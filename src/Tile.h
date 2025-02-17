/**

@file Tiles.h

@brief Declares the Tile class for grid - based map structure.

*/

#ifndef TILES_H
#define TILES_H

#include "Entity.h"

class Tile : public Entity
{
public:
    Tile();
    ~Tile();

    enum Type
    {
        Grass,
        Path,
        Entry,
        Exit
    };

    virtual Type getType() 
    {
        return m_type;
    }

    virtual void setType(Type newType)
    {
        m_type = newType;
    }

private:
    Type m_type;

};


#endif
