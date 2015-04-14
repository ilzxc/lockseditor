//
//  Snapshots.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/11/14.
//
//

#ifndef __MetaLocksEditor__Snapshots__
#define __MetaLocksEditor__Snapshots__

#include "House.h"
#include "cinder/gl/gl.h"

class Snapshots
{
  public:
    Snapshots();
    
    void saveHouse( const int index, const House& house ) { house_snapshots[ index ] = std::make_shared< House >( house ); }
    const std::shared_ptr< House > loadHouse( const int index ) { return house_snapshots[ index ]; }
    
    void draw() const;
    
  private:
    std::vector< std::shared_ptr< House > > house_snapshots;
};

#endif /* defined(__MetaLocksEditor__Snapshots__) */
