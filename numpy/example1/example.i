 /* example.i */
 
%module example


 
%{ 
 /* Put header files here or function declarations like below */
 #include "example.h"
 %}
 
%include "example.h"
%include "carrays.i"
%array_functions(klass *, klassArray);

/*%typemap(out) klass * {
   printf("called \n");
   $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), SWIGTYPE_p_klass, 0 |  0 );
}*/
%inline %{
static void createKlasses( klass * klassArray[], int size)
{
   //klass c;
   for(int i = 0; i < size; i++)
   {
      klassArray[i] = new klass();
   }
}
%}

