#include "objmodelloader.h"

ObjModelLoader::ObjModelLoader()
{

}

bool ObjModelLoader::loadObjFile(std::string sObjFileName) {
    QFile qfile;
    if (qfile.exists(QString(sObjFileName.c_str()))) {
        return false;
    }
    int nline = 0;

    uint32_t nVertexCount = 0, nNormalCount = 0, nUVCount = 0;
    std::ifstream ifs(sObjFileName);
    std::string value;
    while (std::getline(ifs, value)) {
        nline++;
        if (value.length() <= 5) continue;
        QStringList qslSingleData = QString(value.c_str()).split(' ', Qt::SkipEmptyParts);
        if (qslSingleData.size() <= 3) {
            qDebug() << "obj file seems has problem in line " << nline;
            continue;
        }

        data.nVertexCount = data.vertex.size();
        data.nIndicesCount = data.indices.size();

        if (qslSingleData[0] == 'v') {
            if (data.nVertexCount <= nVertexCount) {
                ObjVertexData vertex;
                vertex.position = QVector3D(qslSingleData[1].toFloat(), qslSingleData[2].toFloat(), qslSingleData[3].toFloat());
                data.vertex.push_back(vertex);
            }
            nVertexCount++;
        } else if (qslSingleData[0] == 'f') {
            ObjIndicesData indices;
            indices.index = qslSingleData[0].toFloat();
            data.indices.push_back(indices);
        }
    }

    return true;
}
