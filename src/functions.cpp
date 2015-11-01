#include "functions.h"

/** CreateFileA */
createFile_t createFile_orig = (createFile_t)CreateFileA;
findFirstFile_t findFirstFile_orig = (findFirstFile_t)FindFirstFileA;
deleteFile_t deleteFile_orig = (deleteFile_t)DeleteFileA;
copyFile_t copyFile_orig = (copyFile_t)CopyFileA;
getFileAttributes_t getFileAttributes_orig = (getFileAttributes_t)GetFileAttributesA;
setFileAttributes_t setFileAttributes_orig = (setFileAttributes_t)SetFileAttributesA;
/**	Adds a label to the Dark Omen Gui */
addLabel_t addLabel_orig = (addLabel_t)0x4855A0;
/** Assigns a label to a Dark Omen Gui Element */
setTooltip_t setTooltip_orig = (setTooltip_t)0x486300;
sub_487640_t sub_487640 = (sub_487640_t)0x487640;
sub_41C320_t sub_41C320 = (sub_41C320_t)0x41C320;
getTextWidth_t getTextWidth_orig = (getTextWidth_t)0x481930;
getFontHeight_t getFontHeight_orig = (getFontHeight_t)0x4819D0;
addLabelEventHandler_t addLabelEventHandler_orig = (addLabelEventHandler_t)0x484E60;
eventFunc_t menuMenuLabelHovered_orig = (eventFunc_t)0x42C750;
noarg_int_t optionMenu_orig = (noarg_int_t)0x4140D0;
createScene_t createScene_orig = (createScene_t)0x483A80;
openSpriteFile_t openSpriteFile_orig = (openSpriteFile_t)0x4821C0;
addListCtrl_t addListCtrl_orig = (addListCtrl_t)0x485CE0;
replacePath_t replacePath_orig = (replacePath_t)0x48A010;
disableLabel_t disableLabel_orig = (disableLabel_t)0x4878F0;
getSelectedListIndex_t getSelectedListIndex_orig = (getSelectedListIndex_t)0x4878A0;
freeScene_t freeScene_orig = (freeScene_t)0x483D40;

intarg_int_t sub_418020 = (intarg_int_t)0x418020;
noarg_int_t sub_4820A0 = (noarg_int_t)0x4820A0;

intarg_int_t sub_483FF0 = (intarg_int_t)0x483FF0;
intarg_int_t sub_484860 = (intarg_int_t)0x484860;
intarg_int_t sub_484C40 = (intarg_int_t)0x484C40;
