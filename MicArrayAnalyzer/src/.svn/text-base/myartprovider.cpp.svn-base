/**********************************************************************

  My own class derived from wxArtProvider

  myartprovider.cpp

  Luca Novarini

**********************************************************************/

#include "myartprovider.h"
#include "icons.h"

wxBitmap MyArtProvider::CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
   {
   //Icons
   if(id == _("check_icon"))        return GetBitmapFromMemory(check_icon);
   if(id == _("cross_icon"))        return GetBitmapFromMemory(cross_icon);
   if(id == _("warning_icon"))      return GetBitmapFromMemory(warning_icon);
   if(id == _("play_icon"))         return GetBitmapFromMemory(play_icon);
   if(id == _("stop_icon"))         return GetBitmapFromMemory(stop_icon);
   if(id == _("pause_icon"))        return GetBitmapFromMemory(pause_icon);
   if(id == _("speedup_icon"))      return GetBitmapFromMemory(speedup_icon);
   if(id == _("slowdown_icon"))     return GetBitmapFromMemory(slowdown_icon);
   if(id == _("rulers_menu_icon"))  return GetBitmapFromMemory(rulers_menu_icon);
   
   //Images
   if(id == _("xruler_bgnd"))       return GetBitmapFromMemory(xruler_bgnd);
   if(id == _("yruler_bgnd"))       return GetBitmapFromMemory(yruler_bgnd);
   
   return wxNullBitmap;
   }


void InitArtProvider()
   {
   wxArtProvider::Push(new MyArtProvider);
   }

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: c05d7383-e7cd-410e-b7b8-f45f47c9e283
