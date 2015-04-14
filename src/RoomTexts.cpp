//
//  RoomTexts.cpp
//  MetaLocksEditor
//
//  Created by Husband :) on 12/10/14.
//
//

#include "RoomTexts.h"

using namespace ci;

RoomTexts::RoomTexts()
:font( Font( app::loadResource( "ADAM.CG PRO.otf" ), 24 ) )
{ }

RoomTexts::~RoomTexts() { }

void RoomTexts::setup( const std::vector< std::string >& roomIds )
{
    for ( auto& id : roomIds ) {
        TextBox tb = TextBox().alignment( TextBox::LEFT )
                              .font( font )
                              .size( TextBox::GROW, TextBox::GROW )
                              .text( id );
        tb.setColor( Color( 1.f, 1.f, 1.f ) );
        textures.push_back( tb.render() );
    }
}

void RoomTexts::updateRoom( const int index, const std::string& newId )
{
    if ( index > textures.size() - 1 ) return;
    
    TextBox tb = TextBox().alignment( TextBox::LEFT )
                          .font( font )
                          .size( TextBox::GROW, TextBox::GROW )
                          .text( newId );
    textures[ index ] = tb.render();
}
