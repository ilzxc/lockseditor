//
//  LockEditor.h
//  MetaLocksEditor
//
//  Created by Husband :) on 12/8/14.
//
//

#ifndef __MetaLocksEditor__LockEditor__
#define __MetaLocksEditor__LockEditor__

#include "Lock.h"
#include "cinder/gl/gl.h"
#include "cinder/Rect.h"
#include "cinder/Color.h"

struct LockEditor
{
  public:
    LockEditor();
    LockEditor( const LockEditor& other );
    ~LockEditor();
    void draw( const Lock& lock ) const;
    
  private:
    const ci::Rectf directionButton;
    const ci::Color arrowColor;
    const ci::Color buttonLockedColor,
                    buttonInactiveColor,
                    buttonUnlockedColor;
    
    void drawLeft() const;
    void drawUp() const;
    void drawRight() const;
    void drawDown() const;
};

#endif /* defined(__MetaLocksEditor__LockEditor__) */
