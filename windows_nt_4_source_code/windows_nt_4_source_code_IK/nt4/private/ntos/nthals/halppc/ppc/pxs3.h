/*++

Copyright (c) 1992  ACER Labs Inc.

Module Name:

    pxs3.h

Abstract:

    This header file defines the S3 86C911 GUI accelerator registers.

Author:

    Version 1.0 Kevin Chen  2-Apr-1992
    Version 2.0 Andrew Chou Nov-24-1992
    Version 3.0 Jess Botts  Oct-06-1993   Power PC Initial Version

--*/

#define VERTICALRESOLUTION      768
#define HORIZONTALRESOLUTION    1024
#define OriginalPoint   0
#define BLUE 192
#define WHITE 255
#define CRT_OFFSET 2
#define SEQ_OFFSET 27
#define GRAPH_OFFSET 32
#define ATTR_OFFSET 41

//
// Define virtual address of the video memory and control registers.
//

extern PVOID HalpIoControlBase;

//
// Define S3 register I/O Macros
//

//=============================================================================
//
//  IBMBJB  Changed the semicolons separating statements in the write macros to
//          commas so that if the macro is used as the only statement in a loop
//          all of the statements in the macro will be part of the loop.
//
//          Commas were used instead of putting braces around the statements
//          because if the macro is used in the true part of a conditional the
//          braces will cause the compiler to generate a syntax error.

#define WRITE_S3_UCHAR(port,data)                 \
      *(volatile unsigned char *)((ULONG)HalpIoControlBase + (port)) = (UCHAR)(data), \
      KeFlushWriteBuffer()

#define WRITE_S3_USHORT(port,data)                \
      *(volatile PUSHORT)((ULONG)HalpIoControlBase + (port)) = (USHORT)(data), \
      KeFlushWriteBuffer()

#define READ_S3_UCHAR(port)                       \
      *(volatile unsigned char *)((ULONG)HalpIoControlBase + (port))

#define READ_S3_USHORT(port)                      \
      *(volatile unsigned short *)((ULONG)HalpIoControlBase + (port))

#define READ_S3_VRAM(port)                        \
      *(HalpVideoMemoryBase + (port))

#define WRITE_S3_VRAM(port,data)                  \
      *(HalpVideoMemoryBase + (port)) = (data),   \
      KeFlushWriteBuffer()

//=============================================================================

#define DISPLAY_BITS_PER_PIXEL 8        // display bits per pixel
#define NUMBER_OF_COLORS 256            // number of colors

#define CURSOR_WIDTH 64                 // width of hardware cursor
#define CURSOR_HEIGHT 64                // height of hardware cursor
#define CURSOR_BITS_PER_PIXEL 2         // hardware cursor bits per pixel

//
// S3 86C911 GUI, accelerator Video Controller Definitions.
//
// Define video register format.
//
#define PosID_LO             0x100         // R/W
#define PosID_HI             0x101         // R/W
#define Setup_OP             0x102         // R/W
#define Chck_Ind             0x105         //  R
#define Mono_3B4             0x3B4         // R/W
#define Mono_3B5             0x3B5         // R/W
#define MDA_Mode             0x3B8         //  W
#define HGC_SLPEN            0x3B9         // R/W
#define Stat1_MonoIn         0x3BA         //  R
#define FC_MonoW             0x3BA         //  W
#define HGC_CLPEN            0x3BB         //  W
#define HGC_Config           0x3BF         //  W
#define Attr_Index           0x3C0         // R/W
#define Attr_Data            0x3C0         // R/W
#define Stat0_In             0x3C2         //  R
#define MiscOutW             0x3C2         //  W
#define VSub_EnB             0x3C3         // R/W
#define Seq_Index            0x3C4         // R/W
#define Seq_Data             0x3C5         // R/W
#define DAC_Mask             0x3C6         // R/W
#define DAC_RIndex           0x3C7         //  W
#define DAC_Status           0x3C7         //  W
#define DAC_WIndex           0x3C8         // R/W
#define DAC_Data             0x3C9         // R/W
#define FC_Read              0x3CA         //  R
#define MiscOutR             0x3CC         //  R
#define GC_Index             0x3CE         // R/W
#define GC_Data              0x3CF         // R/W
#define S3_3D4_Index         0x3D4         // R/W
#define S3_3D5_Data          0x3D5         // R/W

#define CGA_Mode             0x3D8         //  W
#define CGA_Color            0x3D9         //  W
#define Stat1_In             0x3DA         //  R
#define FC_Write             0x3DA         //  W
#define CLPEN                0x3DB
#define SLPEN                0x3DC

//
//  Define Enhanced registers for S3_86C911
//

#define SUBSYS_STAT          0x42E8        //  R
#define SUBSYS_CNTL          0x42E8        //  W
#define SUBSYS_ENB           0x46E8        // R/W
#define ADVFUNC_CNTL         0x4AE8        //  W
#define CUR_Y                0x82E8        // R/W
#define CUR_X                0x86E8        // R/W
#define DESTY                0x8AE8        //  W
#define AXIAL_STEP           0x8AE8        //  W
#define DESTX                0x8EE8        //  W
#define DIAG_STEP            0x8EE8        //  W
#define ERR_TERM             0x92E8        //  R
#define MAJ_AXIS_PCNT        0x96E8        //  W
#define RWIDTH               0x96E8        //  W
#define GP_STAT              0x9AE8        //  R
#define DRAW_CMD             0x9AE8        //  W
#define SHORT_STROKE         0x9EE8        //  W
#define BKGD_COLOR           0xA2E8        //  W
#define FRGD_COLOR           0xA6E8        //  W
#define WRITE_MASK           0xAAE8        //  W
#define READ_MASK            0xAEE8        //  W
#define BKGD_MIX             0xB6E8        //  W
#define FRGD_MIX             0xBAE8        //  W
#define MULTIFUNC_CNTL       0xBEE8        //  W
#define RHEIGHT              0xBEE8        //  W
#define PIX_TRANS            0xE2E8        //  W


//
// Define Attribute Controller Indexes : ( out 3C0, Index )
//

#define  PALETTE0            0
#define  PALETTE1            1
#define  PALETTE2            2
#define  PALETTE3            3
#define  PALETTE4            4
#define  PALETTE5            5
#define  PALETTE6            6
#define  PALETTE7            7
#define  PALETTE8            8
#define  PALETTE9            9
#define  PALETTE10          10
#define  PALETTE11          11
#define  PALETTE12          12
#define  PALETTE13          13
#define  PALETTE14          14
#define  PALETTE15          15
#define  ATTR_MODE_CTRL     16
#define  BORDER_COLOR       17
#define  COLOR_PLANE_ENABLE 18
#define  HORI_PIXEL_PANNING 19
#define  PIXEL_PADDING      20

//
// Define Sequencer Indexes  ( out 3C4, Index)
//

#define  RESET                 0
#define  CLOCKING_MODE         1
#define  ENABLE_WRITE_PLANE    2
#define  CHARACTER_FONT_SELECT 3
#define  MEMORY_MODE_CONTROL   4

//
// Define Graphics Controller Index  ( out 3CE, Index )
//

#define SET_RESET            0
#define ENABLE_SET_RESET     1
#define COLOR_COMPARE        2
#define DATA_ROTATE          3
#define READ_PLANE_SELECT    4
#define GRAPHICS_CTRL_MODE   5
#define MEMORY_MAP_MODE      6
#define COLOR_DONT_CARE      7
#define BIT_MASK             8

//
// Define CRTC, VGA S3, SYS_CTRL Index : ( Out 3D4, Index )
//
// Define CRTC Controller Indexes
//

#define HORIZONTAL_TOTAL                    0
#define HORIZONTAL_DISPLAY_END              1
#define START_HORIZONTAL_BLANK              2
#define END_HORIZONTAL_BLANK                3
#define HORIZONTAL_SYNC_POS                 4
#define END_HORIZONTAL_SYNC                 5
#define VERTICAL_TOTAL                      6
#define CRTC_OVERFLOW                       7
#define PRESET_ROW_SCAN                     8
#define MAX_SCAN_LINE                       9
#define CURSOR_START                       10
#define CURSOR_END                         11
#define START_ADDRESS_HIGH                 12
#define START_ADDRESS_LOW                  13
#define CURSOR_LOCATION_HIGH               14
#define CURSOR_FCOLOR                      14
#define CURSOR_BCOLOR                      15
#define CURSOR_LOCATION_LOW                15
#define VERTICAL_RETRACE_START             16
#define VERTICAL_RETRACE_END               17
#define VERTICAL_DISPLAY_END               18
#define OFFSET_SCREEN_WIDTH                19
#define UNDERLINE_LOCATION                 20
#define START_VERTICAL_BLANK               21
#define END_VERTICAL_BLANK                 22
#define CRT_MODE_CONTROL                   23
#define LINE_COMPARE                       24
#define CPU_LATCH_DATA                     34
#define ATTRIBUTE_INDEX1                   36
#define ATTRIBUTE_INDEX2                   38

//
// Define VGA S3 Indexes
//
#define S3R0                               0x30
#define S3R1                               0x31
#define S3R2                               0x32
#define S3R3                               0x33
#define S3R4                               0x34
#define S3R5                               0x35
#define S3R6                               0x36
#define S3R7                               0x37
#define S3R8                               0x38
#define S3R9                               0x39
#define S3R0A                              0x3A
#define S3R0B                              0x3B
#define S3R0C                              0x3C
#define SC0                                0x40
#define SC2                                0x42
#define SC3                                0x43
#define SC5                                0x45

//
// Define System Control Indexes
//
#define SYS_CNFG                           64
#define SOFT_STATUS                        65
#define MODE_CTRL                          66
#define EXT_MODE                           67
#define HGC_MODE                           69
#define HGC_ORGX0                          70
#define HGC_ORGX1                          71
#define HGC_ORGY0                          72
#define HGC_ORGY1                          73
#define HGC_YSTART0                        76
#define HGC_YSTART1                        77
#define HGC_DISPX                          78
#define HGC_DISPY                          79

#define ENABLE_HARDWARE_CURSOR     1
#define DISABLE_HARDWARE_CURSOR    0

//
// define advanced function control register structure
//
#define RES_640x480                             0
#define RES_1024x768                            1
#define RES_800x600                             1

#define ENABLE_VGA             6
#define ENABLE_ENHANCED        7

//
// define draw command register values
//
#define NOP_COMMAND            0x0
#define DRAW_LINE_COMMAND      0x2000
#define RECTANGLE_FILL_COMMAND 0x4000
#define BITBLT_COMMAND         0xc000
#define BYTE_SWAP              0x1000
#define NO_BYTE_SWAP           0x0
#define SIXTEEN_BIT_BUS        0x0200
#define EIGHT_BIT_BUS          0x0
#define WAIT                   0x0100
#define NO_WAIT                0x0
#define R0                     0x0
#define R45                    0x20
#define R90                    0x40
#define R135                   0x60
#define R180                   0x80
#define R225                   0xa0
#define R270                   0xc0
#define R315                   0xe0
#define XMAJ                   0x0
#define YMAJ                   0x40
#define XPositive              0x20
#define YPositive              0x80
#define XNegative              0x0
#define YNegative              0x0

#define DRAW_YES               0x10
#define DRAW_NO                0x0
#define RADIAL                 8
#define XY_BASE                0
#define LAST_PIXEL_OFF         4
#define LAST_PIXEL_ON          0
#define MULTIPLE_PIXEL         2
#define SINGLE_PIXEL           0
#define DRAW_READ              0
#define DRAW_WRITE             1

#define SSV_DRAW               0x1000
#define SSV_MOVE               0x0

#define OneEmpty             0x80
#define TwoEmpty             0x40
#define ThreeEmpty           0x20
#define FourEmpty            0x10
#define FiveEmpty            0x8
#define SixEmpty             0x4
#define SevenEmpty           0x2
#define EightEmpty           0x1

#define BACKGROUND_COLOR                                 0
#define FOREGROUND_COLOR                                 0x20
#define CPU_DATA                                         0x40
#define DISPLAY_MEMORTY                                  0x60
#define NOT_SCREEN                                       0
#define LOGICAL_ZERO                                     1
#define LOGICAL_ONE                                      2
#define LEAVE_ALONE                                      3
#define NOT_NEW                                          4
#define SCREEN_XOR_NEW                                   5
#define NOT_SCREEN_XOR_NEW                               6
#define OVERPAINT                                        7  //( NEW )
#define NOT_SCREEN_OR_NOT_NEW                            8
#define SCREEN_OR_NOT_NEW                                9
#define NOT_SCREEN_OR_NEW                               10
#define SCREEN_OR_NEW                                   11
#define SCREEN_AND_NEW                                  12
#define NOT_SCREEN_AND_NEW                              13
#define SCREEN_AND_NOT_NEW                              14
#define NOT_SCREEN_AND_NOT_NEW                          15

#define BEE8_1H   1
#define BEE8_2H   2
#define BEE8_3H   3
#define BEE8_4H   4
#define BEE8_0H   0
#define L_CLIP    0x1000
#define R_CLIP    0x2000
#define B_CLIP    0x3000
#define T_CLIP    0x4000

#define DATA_EXTENSION  0xa000  // 10100000B
#define CPU_EXT         0x80
#define DISPLAY_EXT     0xc0
#define NO_EXTENSION    0x0
#define PACK_DATA       0x4
#define NO_PACK_DATA    0x0
#define SET_THIS_BIT_TO_ZERO  0;

//
// Define bits per pixel codes.
//
#define ONE_BIT_PER_PIXEL 0             // 1-bit per pixel
#define TWO_BITS_PER_PIXEL 1            // 2-bits per pixel
#define FOUR_BITS_PER_PIXEL 2           // 4-bits per pixel
#define EIGHT_BITS_PER_PIXEL 3          // 8-bits per pixel

//
// Define address step value.
//
#define ADDRESS_STEP_INCREMENT 1        // vram transfer address increment

//
// Define cross hair thickness values.
//
#define ONE_PIXEL_THICK 0x0             // one pixel in thickness
#define THREE_PIXELS_THICK 0x1          // three pixels in thickness
#define FIVE_PIXELS_THICK 0x2           // five pixels in thickness
#define SEVEN_PIXELS_THICK 0x3          // seven pixels in thickness

//
// Define multiplexer control values.
//
#define ONE_TO_ONE 0x0                  // 1:1 multiplexing
#define FOUR_TO_ONE 0x1                 // 4:1 multiplexing
#define FIVE_TO_ONE 0x2                 // 5:1 multiplexing

//
// Define cursor origin values.
//

#define CURSOR_X_ORIGIN (((2*HORIZONAL_SYNC_VALUE)+BACK_PORCH_VALUE)*4-36)
#define CURSOR_Y_ORIGIN ((VERTICAL_BLANK_VALUE/2)+24)

ULONG HotspotX, HotspotY;

// Extended VGA BIOS
#define SUPER_VGA_SUPPORT             4FH
#define RET_EXT_VGA_INFO              00H
#define RET_EXT_VGA_MODE_INFO         01H
#define SET_EXT_VGA_MODE              02H
#define QUERY_CUR_EXT_VGA_MODE        03H

#define SAVE_RESTORE_FUNCTION         04H
//    Function 04.0    Query Save/Restore Buffer Size
#define GET_SAVE_BUFFER_SIZE          00H
//    Function 04.1    Save Extended Video state
#define SAVE_STATE                    01H
//    Function 04.2    Restore Extended VGA state
#define RESTORE_STATE                 02H

#define WINDOWS_CONTROL               05H
//    Function 05.0    Set Window Control
#define SELECT_PAGE_TO_BE_MAPPED      00H
//    fUNCTION 05.1    Get Window Control Setting
#define GET_PAGE_MAPPED               01H

#define SET_RESET_DUAL_DISPLAY_MODE   FFH

BOOLEAN  ColorMonitor;
PVOID S3_3x4, S3_3x5;

