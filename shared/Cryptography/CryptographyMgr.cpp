#include "CryptographyMgr.h"
#include "Logs/Log.h"

template<> CryptographyMgr*  Singleton<CryptographyMgr>::m_instance = 0;

CryptographyMgr::CryptographyMgr()
{
    m_privateKey = CryptoPP::InvertibleRSAFunction();
    m_publicKey = QByteArray();
}

CryptographyMgr::~CryptographyMgr() {}

bool CryptographyMgr::Initialize()
{
    if (LoadKeyPair())
        return true;
    else
        return GenerateKeyPair();
}

bool CryptographyMgr::GenerateKeyPair()
{
    QDir dir;
    dir.mkdir("cryptography");

    CryptoPP::AutoSeededRandomPool prng;

    CryptoPP::InvertibleRSAFunction privateKey;
    privateKey.Initialize(prng, 1024);

    CryptoPP::RSAFunction publicKey(privateKey);

    CryptoPP::FileSink privKeyFile("cryptography/wakbox.ppk");
    CryptoPP::FileSink pubKeyFile("cryptography/wakbox.pub");

    privateKey.Save(privKeyFile);
    publicKey.Save(pubKeyFile);

    return LoadKeyPair();
}

bool CryptographyMgr::LoadKeyPair()
{
    if (!QFile::exists("cryptography/wakbox.ppk"))
        return false;

    CryptoPP::FileSource privKeyFile("cryptography/wakbox.ppk", true);
    m_privateKey.Load(privKeyFile);

    QFile pubKeyFile("cryptography/wakbox.pub");
    if (!pubKeyFile.open(QIODevice::ReadOnly))
        return false;

    m_publicKey = pubKeyFile.readAll();
    return true;
}

QByteArray CryptographyMgr::Decrypt(QByteArray buffer)
{
    CryptoPP::AutoSeededRandomPool prng;
    std::string result;

    CryptoPP::RSAES_PKCS1v15_Decryptor d(m_privateKey);
    CryptoPP::StringSource((byte*)buffer.data(), (size_t)buffer.size(), true,
            new CryptoPP::PK_DecryptorFilter(prng, d, new CryptoPP::StringSink(result)));

    return QString::fromStdString(result).toLatin1();
}
