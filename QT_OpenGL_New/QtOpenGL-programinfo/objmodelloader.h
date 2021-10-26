#ifndef OBJMODELLOADER_H
#define OBJMODELLOADER_H

#include <string>
#include <vector>
#include <fstream>

#include <QFile>
#include <QString>
#include <QDebug>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLFunctions>

struct ObjVertexData
{
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
};

struct ObjIndicesData
{
    uint32_t index;
};

struct ObjData
{
    std::vector<ObjVertexData> vertex;
    std::vector<ObjIndicesData> indices;
    uint32_t nVertexCount;
    uint32_t nIndicesCount;
};

class ObjModelLoader
{
public:
    ObjModelLoader();

    bool loadObjFile(std::string sObjFileName);

private:
    ObjData data;

};

#endif // OBJMODELLOADER_H
