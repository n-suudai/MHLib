
#import "MetalViewController.h"
#include "MH/OS/Types.hpp"
#include "MH/KeyCode.hpp"
#include "MH/MH.hpp"
#include <memory>


using namespace MH;


KEY_CODE TranslateKey(u16 keyCode)
{
    constexpr KEY_CODE keyTable[127] = {
        /* 0x00 */ KEY_CODE_A, // kVK_ANSI_A
        /* 0x01 */ KEY_CODE_S, // kVK_ANSI_S
        /* 0x02 */ KEY_CODE_D, // kVK_ANSI_D
        /* 0x03 */ KEY_CODE_F, // kVK_ANSI_F
        /* 0x04 */ KEY_CODE_H, // kVK_ANSI_H
        /* 0x05 */ KEY_CODE_G, // kVK_ANSI_G
        /* 0x06 */ KEY_CODE_Z, // kVK_ANSI_Z
        /* 0x07 */ KEY_CODE_X, // kVK_ANSI_X
        /* 0x08 */ KEY_CODE_C, // kVK_ANSI_C
        /* 0x09 */ KEY_CODE_V, // kVK_ANSI_V
        /* 0x0A */ KEY_CODE_UNKNOWN, // kVK_ISO_Section
        /* 0x0B */ KEY_CODE_B, // kVK_ANSI_B
        /* 0x0C */ KEY_CODE_Q, // kVK_ANSI_Q
        /* 0x0D */ KEY_CODE_W, // kVK_ANSI_W
        /* 0x0E */ KEY_CODE_E, // kVK_ANSI_E
        /* 0x0F */ KEY_CODE_R, // kVK_ANSI_R
        /* 0x10 */ KEY_CODE_Y, // kVK_ANSI_Y
        /* 0x11 */ KEY_CODE_T, // kVK_ANSI_T
        /* 0x12 */ KEY_CODE_1, // kVK_ANSI_1
        /* 0x13 */ KEY_CODE_2, // kVK_ANSI_2
        /* 0x14 */ KEY_CODE_3, // kVK_ANSI_3
        /* 0x15 */ KEY_CODE_4, // kVK_ANSI_4
        /* 0x16 */ KEY_CODE_6, // kVK_ANSI_6
        /* 0x17 */ KEY_CODE_5, // kVK_ANSI_5
        /* 0x18 */ KEY_CODE_UNKNOWN, // kVK_ANSI_Equal
        /* 0x19 */ KEY_CODE_9, // kVK_ANSI_9
        /* 0x1A */ KEY_CODE_7, // kVK_ANSI_7
        /* 0x1B */ KEY_CODE_UNKNOWN, // kVK_ANSI_Minus
        /* 0x1C */ KEY_CODE_8, // kVK_ANSI_8
        /* 0x1D */ KEY_CODE_0, // kVK_ANSI_0
        /* 0x1E */ KEY_CODE_UNKNOWN, // kVK_ANSI_RightBracket
        /* 0x1F */ KEY_CODE_O, // kVK_ANSI_O
        /* 0x20 */ KEY_CODE_U, // kVK_ANSI_U
        /* 0x21 */ KEY_CODE_UNKNOWN, // kVK_ANSI_LeftBracket
        /* 0x22 */ KEY_CODE_I, // kVK_ANSI_I
        /* 0x23 */ KEY_CODE_P, // kVK_ANSI_P
        /* 0x24 */ KEY_CODE_RETURN, // kVK_Return
        /* 0x25 */ KEY_CODE_L, // kVK_ANSI_L
        /* 0x26 */ KEY_CODE_J, // kVK_ANSI_J
        /* 0x27 */ KEY_CODE_UNKNOWN, // kVK_ANSI_Quote
        /* 0x28 */ KEY_CODE_K, // kVK_ANSI_K
        /* 0x29 */ KEY_CODE_UNKNOWN, // kVK_ANSI_Semicolon
        /* 0x2A */ KEY_CODE_UNKNOWN, // kVK_ANSI_Backslash
        /* 0x2B */ KEY_CODE_UNKNOWN, // kVK_ANSI_Comma
        /* 0x2C */ KEY_CODE_UNKNOWN, // kVK_ANSI_Slash
        /* 0x2D */ KEY_CODE_N, // kVK_ANSI_N
        /* 0x2E */ KEY_CODE_M, // kVK_ANSI_M
        /* 0x2F */ KEY_CODE_UNKNOWN, // kVK_ANSI_Period
        /* 0x30 */ KEY_CODE_UNKNOWN, // kVK_Tab
        /* 0x31 */ KEY_CODE_SPACE, // kVK_Space
        /* 0x32 */ KEY_CODE_UNKNOWN, // kVK_ANSI_Grave
        /* 0x33 */ KEY_CODE_DELETE, // kVK_Delete
        /* 0x34 */ KEY_CODE_UNKNOWN,
        /* 0x35 */ KEY_CODE_ESCAPE, // kVK_Escape
        /* 0x36 */ KEY_CODE_UNKNOWN, // NOTE: maybe
        /* 0x37 */ KEY_CODE_UNKNOWN, // kVK_Command
        /* 0x38 */ KEY_CODE_LSHIFT, // kVK_Shift
        /* 0x39 */ KEY_CODE_UNKNOWN, // kVK_CapsLock
        /* 0x3A */ KEY_CODE_UNKNOWN, // kVK_Option
        /* 0x3B */ KEY_CODE_LCONTROL, // kVK_Control
        /* 0x3C */ KEY_CODE_RSHIFT, // kVK_RightShift
        /* 0x3D */ KEY_CODE_UNKNOWN, // kVK_RightOption
        /* 0x3E */ KEY_CODE_RCONTROL, // kVK_RightControl
        /* 0x3F */ KEY_CODE_UNKNOWN, // kVK_Function
        /* 0x40 */ KEY_CODE_UNKNOWN, // kVK_F17
        /* 0x41 */ KEY_CODE_UNKNOWN, // kVK_ANSI_KeypadDecimal
        /* 0x42 */ KEY_CODE_UNKNOWN,
        /* 0x43 */ KEY_CODE_UNKNOWN, // kVK_ANSI_KeypadMultiply
        /* 0x44 */ KEY_CODE_UNKNOWN,
        /* 0x45 */ KEY_CODE_UNKNOWN, // kVK_ANSI_KeypadPlus
        /* 0x46 */ KEY_CODE_UNKNOWN,
        /* 0x47 */ KEY_CODE_UNKNOWN, // kVK_ANSI_KeypadClear
        /* 0x48 */ KEY_CODE_UNKNOWN, // kVK_VolumeUp
        /* 0x49 */ KEY_CODE_UNKNOWN, // kVK_VolumeDown
        /* 0x4A */ KEY_CODE_UNKNOWN, // kVK_Mute
        /* 0x4B */ KEY_CODE_UNKNOWN, // kVK_ANSI_KeypadDivide
        /* 0x4C */ KEY_CODE_RETURN, // kVK_ANSI_KeypadEnter
        /* 0x4D */ KEY_CODE_UNKNOWN,
        /* 0x4E */ KEY_CODE_UNKNOWN, // kVK_ANSI_KeypadMinus
        /* 0x4F */ KEY_CODE_UNKNOWN, // kVK_F18
        /* 0x50 */ KEY_CODE_UNKNOWN, // kVK_F19
        /* 0x51 */ KEY_CODE_UNKNOWN, // kVK_ANSI_KeypadEquals
        /* 0x52 */ KEY_CODE_0, // kVK_ANSI_Keypad0
        /* 0x53 */ KEY_CODE_1, // kVK_ANSI_Keypad1
        /* 0x54 */ KEY_CODE_2, // kVK_ANSI_Keypad2
        /* 0x55 */ KEY_CODE_3, // kVK_ANSI_Keypad3
        /* 0x56 */ KEY_CODE_4, // kVK_ANSI_Keypad4
        /* 0x57 */ KEY_CODE_5, // kVK_ANSI_Keypad5
        /* 0x58 */ KEY_CODE_6, // kVK_ANSI_Keypad6
        /* 0x59 */ KEY_CODE_7, // kVK_ANSI_Keypad7
        /* 0x5A */ KEY_CODE_UNKNOWN, // kVK_F20
        /* 0x5B */ KEY_CODE_8, // kVK_ANSI_Keypad8
        /* 0x5C */ KEY_CODE_9, // kVK_ANSI_Keypad9
        /* 0x5D */ KEY_CODE_UNKNOWN, // kVK_JIS_Yen
        /* 0x5E */ KEY_CODE_UNKNOWN, // kVK_JIS_Underscore
        /* 0x5F */ KEY_CODE_UNKNOWN, // kVK_JIS_KeypadComma
        /* 0x60 */ KEY_CODE_F5, // kVK_F5
        /* 0x61 */ KEY_CODE_F6, // kVK_F6
        /* 0x62 */ KEY_CODE_F7, // kVK_F7
        /* 0x63 */ KEY_CODE_F3, // kVK_F3
        /* 0x64 */ KEY_CODE_F8, // kVK_F8
        /* 0x65 */ KEY_CODE_F9, // kVK_F9
        /* 0x66 */ KEY_CODE_UNKNOWN, // kVK_JIS_Eisu
        /* 0x67 */ KEY_CODE_F11, // kVK_F11
        /* 0x68 */ KEY_CODE_UNKNOWN, // kVK_JIS_Kana
        /* 0x69 */ KEY_CODE_UNKNOWN, // kVK_F13
        /* 0x6A */ KEY_CODE_UNKNOWN, // kVK_F16
        /* 0x6B */ KEY_CODE_UNKNOWN, // kVK_F14
        /* 0x6C */ KEY_CODE_UNKNOWN,
        /* 0x6D */ KEY_CODE_F10, // kVK_F10
        /* 0x6E */ KEY_CODE_UNKNOWN,
        /* 0x6F */ KEY_CODE_F12, // kVK_F12
        /* 0x70 */ KEY_CODE_UNKNOWN,
        /* 0x71 */ KEY_CODE_UNKNOWN, // kVK_F15
        /* 0x72 */ KEY_CODE_UNKNOWN, // kVK_Help
        /* 0x73 */ KEY_CODE_UNKNOWN, // kVK_Home
        /* 0x74 */ KEY_CODE_UNKNOWN, // kVK_PageUp
        /* 0x75 */ KEY_CODE_DELETE, // kVK_ForwardDelete
        /* 0x76 */ KEY_CODE_F4, // kVK_F4
        /* 0x77 */ KEY_CODE_UNKNOWN, // kVK_End
        /* 0x78 */ KEY_CODE_F2, // kVK_F2
        /* 0x79 */ KEY_CODE_UNKNOWN, // kVK_PageDown
        /* 0x7A */ KEY_CODE_F1, // kVK_F1
        /* 0x7B */ KEY_CODE_LEFT, // kVK_LeftArrow
        /* 0x7C */ KEY_CODE_RIGHT, // kVK_RightArrow
        /* 0x7D */ KEY_CODE_DOWN, // kVK_DownArrow
        /* 0x7E */ KEY_CODE_UP, // kVK_UpArrow
    };
    
    if (keyCode < sizeof(keyTable)) {
        return keyTable[keyCode];
    }
    return KEY_CODE_UNKNOWN;
}

@interface MetalViewController()

@end


@implementation MetalViewController
{
    std::unique_ptr<Application> application;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    application = MHCreateApplication();
    
    [[self.view window] makeFirstResponder:self];
}

- (void)viewDidDisappear
{
    application.reset();
}

- (void)_render
{
    // game loop
    if (application->IsAlive())
    {
        application->OnUpdate(0.0);
        application->OnRender();
    }
    else
    {
        [[self.view window] close];
        [NSApp terminate:nil];
    }
}

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    u32 width = static_cast<u32>(size.width);
    u32 height = static_cast<u32>(size.height);
    application->OnResize(width, height);
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    @autoreleasepool {
        [self _render];
    }
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    
}

-(void)mouseMoved:(NSEvent *)theEvent
{
    
}

- (void)mouseExited:(NSEvent *)theEvent
{
    
}

- (void)mouseDown:(NSEvent *)theEvent
{
    NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    u32 x = static_cast<u32>(locationInView.x);
    u32 y = static_cast<u32>(locationInView.y);
    application->OnMouse(x, y, MOUSE_BUTTON_LEFT, true);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    //NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    //u32 x = static_cast<u32>(locationInView.x);
    //u32 y = static_cast<u32>(locationInView.y);
    //application->OnMouse(x, y, MOUSE_BUTTON_LEFT, true);
}

- (void)mouseUp:(NSEvent *)theEvent
{
    NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    u32 x = static_cast<u32>(locationInView.x);
    u32 y = static_cast<u32>(locationInView.y);
    application->OnMouse(x, y, MOUSE_BUTTON_LEFT, false);
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    u32 x = static_cast<u32>(locationInView.x);
    u32 y = static_cast<u32>(locationInView.y);
    application->OnMouse(x, y, MOUSE_BUTTON_RIGHT, true);
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
    //NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    //u32 x = static_cast<u32>(locationInView.x);
    //u32 y = static_cast<u32>(locationInView.y);
    //application->OnMouse(x, y, MOUSE_BUTTON_RIGHT, true);
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
    NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    u32 x = static_cast<u32>(locationInView.x);
    u32 y = static_cast<u32>(locationInView.y);
    application->OnMouse(x, y, MOUSE_BUTTON_RIGHT, false);
}

- (void)otherMouseDown:(NSEvent *)theEvent
{
    NSInteger buttonNumber = [theEvent buttonNumber];

    NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    u32 x = static_cast<u32>(locationInView.x);
    u32 y = static_cast<u32>(locationInView.y);
    
    if (buttonNumber == 2) {
        // middle
        application->OnMouse(x, y, MOUSE_BUTTON_MIDDLE, true);
    }
}

- (void)otherMouseDragged:(NSEvent *)theEvent
{
    NSInteger buttonNumber = [theEvent buttonNumber];

    //NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    //u32 x = static_cast<u32>(locationInView.x);
    //u32 y = static_cast<u32>(locationInView.y);
    
    if (buttonNumber == 2) {
        // middle
        //application->OnMouse(x, y, MOUSE_BUTTON_MIDDLE, true);
    }
}

- (void)otherMouseUp:(NSEvent *)theEvent
{
    NSInteger buttonNumber = [theEvent buttonNumber];
    
    NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    u32 x = static_cast<u32>(locationInView.x);
    u32 y = static_cast<u32>(locationInView.y);
    
    if (buttonNumber == 2) {
        // middle
        application->OnMouse(x, y, MOUSE_BUTTON_MIDDLE, false);
    }
}

- (void)scrollWheel:(NSEvent *)theEvent
{
    double scrollingDeltaY = static_cast<double>([theEvent scrollingDeltaY]);
    
    NSPoint locationInView = [[self view] convertPoint:[theEvent locationInWindow] fromView:nil];
    u32 x = static_cast<u32>(locationInView.x);
    u32 y = static_cast<u32>(locationInView.y);
    
    if ([theEvent hasPreciseScrollingDeltas]) {
        scrollingDeltaY = scrollingDeltaY * 0.1;
    }
    else {
        scrollingDeltaY = scrollingDeltaY;
    }
    application->OnMouseWheel(x, y, scrollingDeltaY);
}

- (void)keyDown:(NSEvent *)theEvent
{
    KEY_CODE keyCode = TranslateKey([theEvent keyCode]);
    application->OnKey(keyCode, true);
    
    // Escape キーで終了
    if (keyCode == KEY_CODE_ESCAPE)
    {
        [[self.view window] close];
        [NSApp terminate:nil];
    }
}

- (void)keyUp:(NSEvent *)theEvent
{
    KEY_CODE keyCode = TranslateKey([theEvent keyCode]);
    application->OnKey(keyCode, false);
}

@end




