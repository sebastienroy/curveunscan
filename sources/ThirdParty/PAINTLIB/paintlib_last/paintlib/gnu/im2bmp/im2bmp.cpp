

#include "im2bmp.h"



std::string filein; 

std::string fileout; 



void main(int nargs, char** args)

{

  PLAnyBmp bmp;

  PLAnyPicDecoder decoder;

  PLBmpEncoder encoder;



  if (nargs==1)

  {

    printusemessage();

    exit(0);

  }



  parseargs(nargs, args);

  

  // Open the graphic file.  

  try 

  {

    decoder.MakeBmpFromFile(filein.c_str(),

	 &bmp);



    encoder.MakeFileFromBmp(fileout.c_str(),

	 &bmp);

    exit(0);

  }

  catch (PLTextException e)

  {

    std::cerr<<"\nim2bmp: "<<(const char*)e <<std::endl;

    exit(1);

  }

}



//----------------------------------------

//

// FUNCTION: parseargs

//

// PORPOUSE: Parse command line arguments

//

//----------------------------------------

void parseargs(int nargs, char** args)

{

  int i;

	

  for (i=1; i<nargs; i++)

  {

	std::string arg(args[i]);

	if (arg=="-o")

	{

      i++;

      if (i<nargs)

	  {

        fileout = args[i];

	  }

      else

	  {

        std::cerr << "im2bmp: -o needs a file name.\n";			  

		exit(1);

	  }

	}

    else

	{

	  if (filein.empty())

		filein = args[i];

	  else

	  {

            std::cerr << "im2bmp: Only accepts one file input.\n"; 

            exit(1);

	  }

	}

  }



  if (fileout.empty())

  {

    fileout = filein.substr(0,filein.size()-4);

    fileout+=".bmp";

  }

  

  std::cerr<<"im2bmp: Input file: "<<filein<<std::endl;			  

  std::cerr<<"im2bmp: Output file: "<<fileout<<std::endl;			  

}



//-------------------------------------------

//

// FUNCTION: printusemessage

//

// PORPOUSE: Print help abaut program use.

//

//-------------------------------------------

void printusemessage()

{

  std::cerr << "\nim2bmp: Jose Miguel Buenaposada (jmbuena@dia.fi.upm.es) ---------------\n";

  std::cerr << "Use: im2bmp <filein> [-o fileout]\n";

  std::cerr << "   -o fileout: name of the output file.\n";

}

