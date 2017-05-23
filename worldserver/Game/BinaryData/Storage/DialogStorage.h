#ifndef BINARYDATA_DIALOGSTORAGE_H
#define BINARYDATA_DIALOGSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class DialogStorage : public BinaryDataStorage<T>
{
public:
    DialogStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            DialogBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_criteria = this->_reader->ReadString();

            qint32 answerCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < answerCount; ++i)
            {
                Answer answer;

                answer.m_id = this->_reader->ReadInt();
                answer.m_criterion = this->_reader->ReadString();
                answer.m_type = this->_reader->ReadInt();
                answer.m_clientOnly = this->_reader->ReadBool();

                entry.m_answers.push_back(answer);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for DialogStorage";
    }
};

#endif // BINARYDATA_DIALOGSTORAGE_H
