#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "House.h"
#include "HouseEditor.h"
#include "Snapshots.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MetaLocksEditorApp : public AppNative {
  public:
    void prepareSettings( Settings* settings );
    void setup();
    void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
    void keyUp( KeyEvent event );
    void update();
    void draw();
    
  private:
    shared_ptr< House > test;
    shared_ptr< House > save_test;
    shared_ptr< HouseEditor > test_editor;
    shared_ptr< Snapshots > snapshots;
    bool shift;
};

void MetaLocksEditorApp::prepareSettings( Settings* settings )
{
    settings->setWindowSize( 1000, 505 );
    settings->setResizable( false );
}

void MetaLocksEditorApp::setup()
{
    shift = false;
    
    gl::enableAlphaBlending();
    test = make_shared< House >( 4, 4 );
    test_editor = make_shared< HouseEditor >( 500, 500, *test );
    snapshots = make_shared< Snapshots >();
}

void MetaLocksEditorApp::mouseDown( MouseEvent event )
{
    test_editor->mouse( *test, event.getPos(), shift );
}

/// TODO: make a proper keyboard shortcuts class, dude...
void MetaLocksEditorApp::keyDown( KeyEvent event )
{
    cout << event.getCode() << endl;
    
    if ( ( event.getCode() != 303 ) && ( event.getCode() != 304 ) ) {
        if ( event.getCode() == 32 ) {
            save_test = make_shared< House >( *test );
        } else if ( event.getCode() == 13 ) {
            test = make_shared< House >( *save_test );
        } else if ( event.getCode() == 27 ) {
            test->resetIndices();
            // test = make_shared< House >( 4, 4 ); // hard-reset
        }
        
        if ( event.getCode() == 119 ) // W
        {
            test_editor->toggleLockDirection( UP, *test );
        }
        else if ( event.getCode() == 97 ) // A
        {
            test_editor->toggleLockDirection( LEFT, *test );
        }
        else if ( event.getCode() == 115 ) // S
        {
            test_editor->toggleLockDirection( DOWN, *test );
        }
        else if ( event.getCode() ==100 ) // D
        {
            test_editor->toggleLockDirection( RIGHT, *test );
        }
        
        int save = event.getCode() - 48;
        if ( save < 10 && save >= 0 ) {
            if ( shift ) {
                snapshots->saveHouse( save, *test );
            } else {
                if ( snapshots->loadHouse( save ) != nullptr ) {
                    test = make_shared< House >( *snapshots->loadHouse( save ) );
                }
            }
        }
        
        int key = event.getCode() - 273;
        int direction;
        
        switch( key ) {
            case  0  :  direction = UP;    break;
            case  1  :  direction = DOWN;  break;
            case  2  :  direction = RIGHT; break;
            case  3  :  direction = LEFT;  break;
            default  :  return;
        }
        test->movePlayer( direction );
        return;
    }
    shift = true;
}

void MetaLocksEditorApp::keyUp( KeyEvent event )
{
    if ( event.getCode() == 303 || event.getCode() == 304 ) {
        shift = false;
    }
}

void MetaLocksEditorApp::update()
{
}

void MetaLocksEditorApp::draw()
{
    gl::clear( Color( 1, 1, 1 ) );
    gl::pushMatrices();
    test_editor->draw( *test );
    snapshots->draw();
    gl::popMatrices();
}

CINDER_APP_NATIVE( MetaLocksEditorApp, RendererGl )
