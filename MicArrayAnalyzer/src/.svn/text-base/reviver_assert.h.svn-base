namespace tpp
   {
   #ifndef REVIVER_ASSERT_H
   #define REVIVER_ASSERT_H

   /*! \def MyAssertFunction
       \brief Function used by 'Assert' function in _DEBUG mode.

       Details.
   */
   extern bool MyAssertFunction( bool b, const char* desc, int line, const char* file);

   #if defined( _DEBUG )
   #define Assert( exp, description ) tpp::MyAssertFunction( (int)(exp), description, __LINE__, __FILE__ ) // [esseci] aggiunto scope
   #else
      #define Assert( exp, description )
   #endif

   #endif

   }
