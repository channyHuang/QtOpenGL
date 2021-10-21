#ifndef KTXLOADER_H
#define KTXLOADER_H

#include <string>
#include <QOpenGLFunctions_4_2_Core>

struct header
{
    unsigned char       identifier[12];
    unsigned int        endianness;
    unsigned int        gltype;
    unsigned int        gltypesize;
    unsigned int        glformat;
    unsigned int        glinternalformat;
    unsigned int        glbaseinternalformat;
    unsigned int        pixelwidth;
    unsigned int        pixelheight;
    unsigned int        pixeldepth;
    unsigned int        arrayelements;
    unsigned int        faces;
    unsigned int        miplevels;
    unsigned int        keypairbytes;
};

union keyvaluepair
{
    unsigned int        size;
    unsigned char       rawbytes[4];
};

class ktxLoader
{
public:
    ktxLoader();

    unsigned int load(std::string sFilename, unsigned int tex = 0, QOpenGLFunctions_4_2_Core *f = nullptr);
    bool save(std::string sFilename, unsigned int target, unsigned int tex, QOpenGLFunctions_4_2_Core *f);
};

#endif // KTXLOADER_H
