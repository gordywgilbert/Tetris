#ifndef _TETRONIMOS_
#define _TETRONIMOS_


// --------------------------------------------------------------------------------
//                                   TETRONIMOS
// --------------------------------------------------------------------------------

class Pieces
{
public:

	int GetTetronimoType(int pPiece, int pRotation, int pX, int pY);
	int GetXStartingPosition(int pPiece, int pRotation);
	int GetYStartingPosition(int pPiece, int pRotation);
};

#endif // _TETRONIMOS_