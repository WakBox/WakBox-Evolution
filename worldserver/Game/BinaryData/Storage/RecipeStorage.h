#ifndef BINARYDATA_RECIPESTORAGE_H
#define BINARYDATA_RECIPESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class RecipeStorage : public BinaryDataStorage<T>
{
public:
    RecipeStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            RecipeBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_categoryId = this->_reader->ReadInt();
            entry.m_duration = this->_reader->ReadLong();
            entry.m_criteria = this->_reader->ReadString();
            entry.m_visibilityCriteria = this->_reader->ReadString();
            entry.m_level = this->_reader->ReadInt();
            entry.m_properties = this->_reader->ReadIntArray();
            entry.m_xpRatio = this->_reader->ReadInt();
            entry.m_machinesUsingRecipe = this->_reader->ReadIntArray();
            entry.m_successRate = this->_reader->ReadInt();
            entry.m_contractEnabled = this->_reader->ReadBool();
            entry.m_neededKamas = this->_reader->ReadLong();
            entry.m_xp = this->_reader->ReadLong();

            qint32 ingredientCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < ingredientCount; ++i)
            {
                RecipeIngredient recipeIngredient;

                recipeIngredient.m_itemId = this->_reader->ReadInt();
                recipeIngredient.m_quantity = this->_reader->ReadShort();

                entry.m_ingredients.push_back(recipeIngredient);
            }


            qint32 productCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < productCount; ++i)
            {
                RecipeProduct recipeProduct;

                recipeProduct.m_itemId = this->_reader->ReadInt();
                recipeProduct.m_quantity = this->_reader->ReadShort();

                entry.m_products.push_back(recipeProduct);
            }


            qint32 materialCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < materialCount; ++i)
            {
                RecipeMaterial recipeMaterial;

                recipeMaterial.m_minLevel = this->_reader->ReadShort();
                recipeMaterial.m_minRarity = this->_reader->ReadShort();
                recipeMaterial.m_optionnal = this->_reader->ReadBool();
                recipeMaterial.m_materialTypes = this->_reader->ReadIntArray();

                entry.m_materials.push_back(recipeMaterial);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for RecipeStorage";
    }
};

#endif // BINARYDATA_RECIPESTORAGE_H
