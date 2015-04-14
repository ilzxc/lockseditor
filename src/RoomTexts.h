//
//  RoomTexts.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/10/14.
//
//

#ifndef __MetaLocksEditor__RoomTexts__
#define __MetaLocksEditor__RoomTexts__

#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/Text.h"

class RoomTexts
{
public:
    RoomTexts();
    ~RoomTexts();
    
    void setup( const std::vector< std::string >& roomIds );
    void updateRoom( const int index, const std::string& newName );
    const ci::gl::Texture& getText( const int room ) const { return textures[ room ]; }
    
private:
    std::vector< ci::gl::Texture > textures;
    ci::Font font;
};

#endif /* defined(__MetaLocksEditor__RoomTexts__) */
