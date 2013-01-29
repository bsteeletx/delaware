
#pragma once

class ParentImage
{
public:
	ParentImage(void);
	~ParentImage(void);

    unsigned int getImageNumber(const char filename[]);
    bool isDifferent(const char filename[]);
    bool isParentImageSet(void);
    void setImage(const char filename[]);

private:

    unsigned int pImageNumber[8];
    char fileLoc[8][32];
};
