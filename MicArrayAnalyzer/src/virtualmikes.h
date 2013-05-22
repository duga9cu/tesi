/**********************************************************************
                      
   Mic Array Analyzer

   virtualmikes.h

   Luca Novarini

**********************************************************************/
#ifndef __VIRTUAL_MIKES_H__
#define __VIRTUAL_MIKES_H__

#define VIRT_MIKES_SET_MIN 10    //Min array size for a mikes set.
#define VIRT_MIKES_SET_INC 10    //Array size increment for memory realloc.

class VirtualMike
   {
      int x,y;
      int id;           //Mic # if mirror = false, Mirror of Mic # if mirror = true!
   public:
      int GetX() { return x; }
      int GetY() { return y; }
      int GetMicID() { return id; }
      VirtualMike(int xpos,int ypos,int mic_id) { x = xpos; y = ypos; id = mic_id; }
   };
   
class VirtualMikesSet
   {
   private:
      VirtualMike** vmHolder;    //An array of pointers that hold Virtual Mikes position and level.
      int iSizeOfArray;          //Size of.
      int iStoredMikes;          //Number of stored mikes.
   public:
      VirtualMikesSet() { iStoredMikes = 0; iSizeOfArray = VIRT_MIKES_SET_MIN; vmHolder = new VirtualMike *[iSizeOfArray]; }
      void AddVirtualMike(int xpos,int ypos,int MicNum)
         {
         if (iStoredMikes >= (iSizeOfArray - 1))   //The array of pointers to VirtualMikes should be resized!
            {
            iSizeOfArray += VIRT_MIKES_SET_INC;    //vmHolder will be resized by a MIKES_SET_INC step size.
            VirtualMike** temp;
            temp = new VirtualMike *[iSizeOfArray];
            for (int i=0;i<(iSizeOfArray - VIRT_MIKES_SET_INC);i++) temp[i] = vmHolder[i];
            delete [] vmHolder;
            vmHolder = temp;
            }
        
        vmHolder[iStoredMikes] = new VirtualMike(xpos,ypos,MicNum);
        iStoredMikes++;
        }
      VirtualMike* GetVirtualMike(int i) { return vmHolder[i]; }
      int GetNumberOfMikes() { return iStoredMikes; }      
   };

#endif
