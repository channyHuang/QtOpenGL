#include "objfileloader.h"

ObjFileLoader::ObjFileLoader()
{

}

bool ObjFileLoader::loadObjFile(std::string sObjFile) {
    qDebug() << "ObjFileLoader::loadObjFile " << sObjFile.c_str();
    bool res = loadObjFile(sObjFile, m_stFileObject);

    pushToData(m_stFileObject);
    return res;
}

bool ObjFileLoader::loadObjFile(std::string sObjFile, FileObject &stFileObject) {
    std::ifstream ifs(sObjFile);
    if (!ifs.is_open()) {
        return false;
    }
    uint32_t count = stFileObject.positions.size();
    QVector3D vec;
    Vector3i veci[3];
    std::string value;
    char tmp[1024];
    while (std::getline(ifs, value)) {
        if (value.length() <= 5) continue;
        switch (value[0]) {
        case 'f':
            sscanf(value.c_str(), "%s %lld/%lld/%lld %lld/%lld/%lld %lld/%lld/%lld", tmp,
                     &veci[0][0], &veci[0][1], &veci[0][2],
                    &veci[1][0], &veci[1][1], &veci[1][2],
                    &veci[2][0], &veci[2][1], &veci[2][2]);

            stFileObject.faces.push_back(Vector3i(veci[0][0] - 1, veci[1][0] - 1, veci[2][0] - 1));

            break;
        case 'v':
            sscanf(value.c_str(), "%s %f %f %f\n", &tmp, &vec[0], &vec[1], &vec[2]);
            if (value[1] == 'n') {
                stFileObject.normals.push_back(vec);
            } else if (value[1] == ' ') {
                stFileObject.positions.push_back(vec + QVector3D(count, count, count));
            }
            break;
        default:
            break;
        }
    }
    ifs.close();
    return (stFileObject.positions.size() == stFileObject.normals.size());
}

bool ObjFileLoader::pushToData(FileObject &stFileObject) {
/*    m_data.resize(stFileObject.positions.size() * 6);
    m_count = 0;

    for (size_t i = 0; i < stFileObject.positions.size(); ++i) {
        GLfloat *p = m_data.data() + m_count;
        *p++ = stFileObject.positions[i].x();
        *p++ = stFileObject.positions[i].y();
        *p++ = stFileObject.positions[i].z();
        *p++ = stFileObject.normals[i].x();
        *p++ = stFileObject.normals[i].y();
        *p++ = stFileObject.normals[i].z();
        m_count += 6;
    }*/
    m_data.resize(stFileObject.faces.size() * 3 * 6);
    m_count = 0;
    for (size_t i = 0; i < stFileObject.faces.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            GLfloat *p = m_data.data() + m_count;
            *p++ = stFileObject.positions[stFileObject.faces[i][j]].x();
            *p++ = stFileObject.positions[stFileObject.faces[i][j]].y();
            *p++ = stFileObject.positions[stFileObject.faces[i][j]].z();
            *p++ = stFileObject.normals[stFileObject.faces[i][j]].x();
            *p++ = stFileObject.normals[stFileObject.faces[i][j]].x();
            *p++ = stFileObject.normals[stFileObject.faces[i][j]].x();
            m_count += 6;
        }
    }


    return true;
}
