#ifndef OBJFILELOADER_H
#define OBJFILELOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <QVector3D>
#include <QDebug>
#include <QOpenGLFunctions>

#include "Vector3i.h"

struct FileObject {
    std::vector<QVector3D> positions;
    std::vector<Vector3i> faces;
    std::vector<QVector3D> normals;
};

class ObjFileLoader
{
public:
    ObjFileLoader();

    const GLfloat *constData() const { return m_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }

    bool loadObjFile(std::string sObjFile);
    bool loadObjFile(std::string sObjFile, FileObject &stFileObject);
    bool pushToData(FileObject &stFileObject);

private:
    QVector<GLfloat> m_data;
    int m_count = 0;

    FileObject m_stFileObject;
};

#endif // OBJFILELOADER_H
