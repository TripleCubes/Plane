#ifndef GRAPHICTYPEDATA_H
#define GRAPHICTYPEDATA_H

class GraphicTypeData {
public:
    virtual void release();

protected:
    bool initialized = false;
    bool released = false;
};

#endif
