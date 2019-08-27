#include <iostream>
#include <stdio.h>
#include <bitset>
#include<fstream>

using namespace std;

//routine work
//----------------------------------------------------------------------------------

class cnode
{
public:
	int info;
	int zoo = NULL;
	cnode *pnext;
	cnode *pleft;
	cnode *pright;
	char letter[8000];
	char zo[200];
};
class cnode2
{
public:
	char zo;
	int in = NULL;
	int flagg = 0;
	cnode2 *pnext;
};
class clist
{
public:
	cnode *phead;
public:
	clist ( )
	{
		phead = NULL;
	}
	/*~clist()
	{

	}*/
	void insert ( cnode *pnn )
	{
		if ( phead == NULL )
		{
			phead = pnn;
		}
		else
		{
			cnode *pb = NULL;
			cnode *ptrav = phead;
			while ( ptrav != NULL )
			{
				if ( ptrav->info > pnn->info )
				{
					break;
				}
				pb = ptrav;
				ptrav = ptrav->pnext;
			}
			if ( pb != NULL )
			{
				pb->pnext = pnn;
			}
			else
			{
				phead = pnn;
			}
			pnn->pnext = ptrav;
		}
	}
	void insert2 ( cnode *pnn )
	{
		if ( phead == NULL )
		{
			phead = pnn;
		}
		else
		{
			cnode *pb = NULL;
			cnode *ptrav = phead;
			while ( ptrav != NULL )
			{
				if ( ptrav->info < pnn->info )
				{
					break;
				}
				pb = ptrav;
				ptrav = ptrav->pnext;
			}
			if ( pb != NULL )
			{
				pb->pnext = pnn;
			}
			else
			{
				phead = pnn;
			}
			pnn->pnext = ptrav;
		}
	}
	void dispall ( )
	{
		cnode *ptrav = phead;
		while ( ptrav != NULL )
		{
			cout << "( " << ptrav->info << " )";
			cout << "( " << ptrav->letter << " )" << endl;
			ptrav = ptrav->pnext;
		}
	}
	void dispall2 ( )
	{
		cnode *ptrav = phead;
		while ( ptrav != NULL )
		{
			cout << "( " << ptrav->zo << " )";
			cout << "( " << ptrav->letter << " )" << endl;
			ptrav = ptrav->pnext;
		}
	}
};
class list
{
public:
	cnode2 *phead, *ptail;
public:
	list ( )
	{
		phead = NULL;
		ptail = NULL;
	}
	~list ( )
	{
		cnode2 *ptrav;
		while ( phead != NULL )
		{
			ptrav = phead;
			phead = phead->pnext;
			delete ptrav;

		}
	}
	void attach ( cnode2 *pnn )
	{
		if ( phead == NULL )
		{
			phead = ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}
	void dispall ( )
	{
		cnode2 *ptrav = phead;
		while ( ptrav != NULL )
		{
			cout << "( " << ptrav->zo << " )";
			ptrav = ptrav->pnext;
		}
	}
};

//----------------------------------------------------------------------------------

//counting the letters in the text
//----------------------------------------------------------------------------------

void counti ( char s[], int &ct, char z[], int k )
{
	for ( int i = 0; s[i] != NULL; i++ )
	{
		if ( s[i] == k ) { ct++; z[k] = k; }
	}
}

//----------------------------------------------------------------------------------

//making the tree
//----------------------------------------------------------------------------------

void beforeroting ( clist &sl, clist &sl2, cnode *pparent )
{
	int i = 0;
	cnode *pnn;
	pnn = new cnode[1];
	sl.phead = pparent->pnext->pnext;
	pparent->pnext->pnext = NULL;
	pnn->info = pparent->info + pparent->pnext->info;
	pnn->pnext = NULL;
	pnn->pleft = NULL;
	pnn->pright = NULL;
	pnn->zo[0] = NULL;
	for ( i = 0; pparent->letter[i] != NULL; i++ )
	{
		pnn->letter[i] = pparent->letter[i];
	}
	for ( int k = 0; pparent->pnext->letter[k] != NULL; k++ )
	{
		pnn->letter[i] = pparent->pnext->letter[k];
		i++;
	}
	pnn->letter[i] = NULL;
	sl.insert ( pnn );
	cnode *pne = pparent->pnext;
	pparent->pnext = NULL;
	sl2.insert2 ( pparent );
	sl2.insert2 ( pne );
}
void rooting ( clist sl, clist &sl2, cnode *pnn )
{
	cnode *pb = NULL;
	cnode *ptrav = sl.phead;
	int i = 0;
	int fff = 0;
	int fff2 = 0;
	int ff = 0;
	int ff2 = 0;
	sl2.phead = pnn->pnext;
	pnn->pnext = NULL;
	while ( ptrav != NULL )
	{
		pb = ptrav;
		for ( int k = 0; ptrav->letter[k] != NULL; k++ )
		{
			if ( pnn->letter[0] == ptrav->letter[k] )
			{
				fff = 1;
			}
			if ( ptrav->pright != NULL&&ptrav->pright->letter[k] != NULL )
			{
				if ( pnn->letter[0] == ptrav->pright->letter[k] )
				{
					fff2 = 1;
				}
			}
		}
		if ( ptrav->pright != NULL )
		{
			if ( fff == 1 && ptrav->pright->letter[1] != NULL&&fff2 == 1 )
			{
				ptrav = ptrav->pright;
			}
			else
			{
				ptrav = ptrav->pleft;
			}
			ff = fff;
			fff = 0;
			ff2 = fff2;
			fff2 = 0;
		}
		else
		{
			if ( fff == 1 )
			{
				ptrav = ptrav->pright;
			}
			else
			{
				ptrav = ptrav->pleft;
			}
			ff = fff;
			fff = 0;
			ff2 = fff2;
			fff2 = 0;
		}
	}
	if ( pb->pright != NULL )
	{
		if ( ff == 1 && pb->pright->letter[1] != NULL&&fff2 == 1 )
		{
			pb->pright = pnn;
			for ( i = 0; pb->zo[i] != NULL; i++ )
			{
				pnn->zo[i] = pb->zo[i];
			}
			pnn->zo[i] = '1';
			pnn->zo[i + 1] = NULL;
			pnn->zoo *= 10;
			pnn->zoo += 1;
		}
		else
		{
			pb->pleft = pnn;
			for ( i = 0; pb->zo[i] != NULL; i++ )
			{
				pnn->zo[i] = pb->zo[i];
			}
			pnn->zo[i] = '0';
			pnn->zo[i + 1] = NULL;
			pnn->zoo *= 10;
		}
	}
	else
	{
		if ( ff == 1 )
		{
			pb->pright = pnn;
			for ( i = 0; pb->zo[i] != NULL; i++ )
			{
				pnn->zo[i] = pb->zo[i];
			}
			pnn->zo[i] = '1';
			pnn->zo[i + 1] = NULL;
			pnn->zoo *= 10;
			pnn->zoo += 1;
		}
		else
		{
			pb->pleft = pnn;
			for ( i = 0; pb->zo[i] != NULL; i++ )
			{
				pnn->zo[i] = pb->zo[i];
			}
			pnn->zo[i] = '0';
			pnn->zo[i + 1] = NULL;
			pnn->zoo *= 10;
		}
	}
	ff = 0;
	ff2 = 0;
}

//----------------------------------------------------------------------------------

//checking is the letter legal and geting it's binary number
//----------------------------------------------------------------------------------
void search ( clist sl, char q, cnode *&pparent, int &d )
{
	int f = 0;
	cnode *ptrav = sl.phead;
	while ( ptrav != NULL )
	{
		if ( ptrav->letter[0] == q&&ptrav->letter[1] == NULL )
		{
			for ( int i = 0; ptrav->zo[i] != NULL; i++ )
			{
				pparent->zo[d] = ptrav->zo[i];
				d++;
			}
			pparent->zoo = ptrav->zoo;
			break;
		}
		for ( int k = 0; ptrav->pleft->letter[k] != NULL; k++ )
		{
			if ( ptrav->pleft->letter[k] == q )
			{
				f = 1;
			}
		}
		if ( f == 1 )
		{
			ptrav = ptrav->pleft;
		}
		if ( f == 0 )
		{
			for ( int k = 0; ptrav->pright->letter[k] != NULL; k++ )
			{
				if ( ptrav->pright->letter[k] == q )
				{
					f = 1;
				}
			}
			if ( f == 1 )
			{
				ptrav = ptrav->pright;
			}
		}
		f = 0;
	}
}

//----------------------------------------------------------------------------------


//diplaying the tree (not important)
//----------------------------------------------------------------------------------

void dispeach ( cnode *ptrav )
{
	if ( ptrav == NULL )
	{
		return;
	}
	dispeach ( ptrav->pleft );
	cout << ptrav->zo[0] << " ";
	cout << ptrav->letter << endl;
	dispeach ( ptrav->pright );


}
void dispall ( clist &sl )
{
	dispeach ( sl.phead );
}

//----------------------------------------------------------------------------------
//get ascii
int getascii ( char x )
{
	char y[255] = { NULL };
	for ( int i = 0; i < 255; i++ )
	{
		y[i] = i;
	}
	for ( int i = 0; i < 255; i++ )
	{
		if ( x == y[i] )
		{
			return i;
		}
	}
}

void main ( )
{
	// variables
	//----------------------------------------------------------------------------------
	char *s, *s2, z[256], bla[200], t = NULL, y = NULL, goal[9999] = { NULL }, gooooool[9999] = { NULL }, answer = NULL, ch = NULL, answer2 = NULL;
	int ct = 0, flag = 0, f2 = 0, m = 1, i = 0, binary = 0, count = 0, flagging = 0, countingtimes = 0, ooh = 0, fo = 0, fi = 0, voo = 0, flagu = 0, cty = 0, p = NULL, noc = 0, no2 = 0, no3 = 0, h = 0, v = 0, f = 0, ww = 0;
	float compression = 0;
	cnode *pnn = NULL, *ptrav = NULL;
	cnode2 *pnn2, *ptravi;
	clist sl, sl2, sl3, sl4;
	list bin, bin2;
	//----------------------------------------------------------------------------------
	//getting the characters
	ifstream file ( "D:\\Data Project Phase 3\\Read2.txt", ifstream::binary );
	file.seekg ( 0, file.end );
	h = file.tellg ( );
	file.seekg ( 0, file.beg );
	s = new char[h];
	for ( i = 0; i < h; i++ )
	{
		file.read ( &s[i], 1 );
	}
	//----------------------------------------------------------------------------------
	//counting don't remember what this is for ?
	for ( i = 0; s[i] != NULL; i++ )
	{
		noc++;
	}
	//listing the letters in a sorted linked list
	//--------------------------------------------------------------------------------------------------------------------------------------------
	for ( int i = 0; i < 256; i++ )
	{
		counti ( s, ct, z, i );
		if ( ct != 0 )
		{
			pnn = new cnode[1];
			pnn->info = ct;
			pnn->letter[0] = z[i];
			pnn->letter[1] = NULL;
			pnn->pnext = NULL;
			pnn->pright = NULL;
			pnn->pleft = NULL;
			pnn->zo[0] = NULL;
			cout << "the letter ( " << pnn->letter << " ) occured ( " << ct << " ) times" << endl;
			sl.insert ( pnn );
		}
		ct = 0;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------------------------------------------
	cout << "the list before editing" << endl;
	sl.dispall ( );
	ptrav = sl.phead;
	while ( ptrav != NULL )
	{
		pnn = new cnode[1];
		pnn->info = ptrav->info;
		pnn->letter[0] = ptrav->letter[0];
		pnn->letter[1] = NULL;
		pnn->pnext = NULL;
		pnn->pright = NULL;
		pnn->pleft = NULL;
		pnn->zo[0] = NULL;
		sl3.insert ( pnn );
		ptrav = ptrav->pnext;
	}
	cout << "the third list" << endl;
	sl3.dispall ( );
	cout << " the first ( " << sl3.phead->zoo << " )" << endl;
	//listing the nodes in a binary tree
	//--------------------------------------------------------------------------------------------------------------------------------------------
	while ( sl.phead->pnext != NULL )
	{
		ptrav = sl.phead;
		beforeroting ( sl, sl2, ptrav );
	}
	cout << endl << "list2 after editing" << endl;
	sl2.dispall ( );
	cout << endl << "list after editing" << endl;
	sl.dispall ( );
	while ( sl2.phead != NULL )
	{
		ptrav = sl2.phead;
		rooting ( sl, sl2, ptrav );
	}
	cout << endl << "list2 after editing" << endl;
	sl2.dispall ( );
	//--------------------------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------
	ptrav = sl3.phead;
	int d = 0;
	while ( ptrav != NULL )
	{
		search ( sl, ptrav->letter[0], ptrav, d );
		ptrav->zo[d] = NULL;
		d = 0;
		for ( int i = 0; i < 200; i++ )
		{
			bla[i] = NULL;
		}
		ptrav = ptrav->pnext;
	}
	cout << "the third list after editing" << endl;
	sl3.dispall2 ( );
	//--------------------------------------------------------------------------------------------------------------------------------------------
	//compressing
	//--------------------------------------------------------------------------------------------------------------------------------------------
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "what do you want to do ?" << endl << "1-For Compression Press [ C ]." << endl << "2-For Decompression Press [ D ]." << endl << "3-For Both Compression & Decompression Press [ B ]." << endl;
	cin >> answer;
	if ( answer == 'C' || answer == 'c' || answer == 'B' || answer == 'b' )
	{
		for ( i = 0; s[i] != NULL; i++ )
		{
			ptrav = sl3.phead;
			while ( ptrav != NULL )
			{
				if ( ptrav->letter[0] == s[i] )
				{
					for ( int k = 0; ptrav->zo[k] != NULL; k++ )
					{
						flagging++;
						if ( ptrav->zo[k] == '1' )
						{
							y = y | ( m << binary );
						}
						if ( count == 7 )
						{
							pnn2 = new cnode2[1];
							pnn2->zo = y;
							pnn2->pnext = NULL;
							bin.attach ( pnn2 );
							y = NULL;
							count = -1;
							binary = -1;
							flagging = 0;
							countingtimes++;
							pnn2->in = 8;
						}
						binary++;
						count++;
					}
					break;
				}
				ptrav = ptrav->pnext;
			}
		}
		if ( flagging != 0 )
		{
			pnn2 = new cnode2[1];
			pnn2->zo = y;
			pnn2->pnext = NULL;
			bin.attach ( pnn2 );
			y = NULL;
			pnn2->in = count;
			countingtimes++;
		}
		cout << "the number of compressed nodes created is  ( " << countingtimes << " )" << endl;
		ofstream compressedfile ( "D:\\Data Project Phase 3\\compressed.txt" );
		ptrav = sl3.phead;
		while ( ptrav != NULL )
		{
			compressedfile.write ( &ptrav->letter[0], 1 );
			compressedfile << "<<" << ptrav->zo << ";";
			ptrav = ptrav->pnext;
		}
		compressedfile << "the";
		/*ptravi = bin.phead;
		while ( ptravi != NULL )
		{
		compressedfile << ptravi->in<<"<<";
		ptravi = ptravi->pnext;
		}
		compressedfile << "the" << endl;*/
		ptravi = bin.phead;
		while ( ptravi != NULL )
		{
			compressedfile.write ( &ptravi->zo, 1 );
			ptravi = ptravi->pnext;
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------------
	//getting compressing ratio
	no2 = noc * 8;
	no3 = countingtimes * 8;
	compression = ( float ) no3 / ( float ) no2;
	compression = 100 - ( compression * 100 );
	//-----------------------------------------------------------------------------------------------------------------------------
	//decompressing
	//-----------------------------------------------------------------------------------------------------------------------------
	if ( answer == 'D' || answer == 'd' || answer == 'B' || answer == 'b' )
	{
		cout << "Do You Want To See The Binary Valu Of Each Node" << endl;
		cin >> answer2;
		ifstream file ( "D:\\Data Project Phase 3\\compressed.txt", ifstream::binary );
		file.seekg ( 0, file.end );
		h = file.tellg ( );
		file.seekg ( 0, file.beg );
		s2 = new char[h];
		v = 0;
		f = 0;
		fo = 0;
		pnn = new cnode[1];
		for ( i = 0; i < h; i++ )
		{
			file.read ( &s2[i], 1 );
			if ( i>3 )
			{
				if ( s2[i] == 'e'&&s2[i - 1] == 'h'&&s2[i - 2] == 't' )
				{
					break;
				}
			}
			if ( f == 1 && ( s2[i] == '0' || s2[i] == '1' ) )
			{
				pnn->zo[v] = s2[i];
				v++;
			}
			if ( f == 0 && fo == 0 )
			{
				pnn->letter[0] = s2[i];
				pnn->letter[1] = NULL;
				fo = 1;
			}
			if ( s2[i] == '<'&&s2[i - 1] == '<' )
			{
				f = 1;
			}
			if ( s2[i] == ';' && ( s2[i - 1] == '0' || s2[i - 1] == '1' ) )
			{
				pnn->zo[v] = NULL;
				pnn->info = NULL;
				pnn->pleft = NULL;
				pnn->pnext = NULL;
				pnn->pright = NULL;
				pnn->zoo = NULL;
				sl4.insert ( pnn );
				f = 0;
				fo = 0;
				v = 0;
				pnn = new cnode[1];
			}
		}
		s2 = new char[h - i];
		int ff = 0;
		f = 0;
		/*pnn2 = new cnode2[1];
		for ( ww = i; ww < h; ww++ )
		{
		file.read ( &s2[ff], 1 );
		if ( i>3 )
		{
		if ( s2[ff] == 'e'&&s2[ff - 1] == 'h'&&s2[ff - 2] == 't' )
		{
		break;
		}
		}
		if ( f == 0 )
		{
		pnn2->in = s2[ff];
		pnn2->flagg = NULL;
		pnn2->pnext = NULL;
		pnn2->zo = NULL;
		bin2.attach ( pnn2 );
		pnn2 = new cnode2[1];
		f = 1;
		}
		if ( s2[ff] == '<'&&s2[ff - 1] == '<' )
		{
		f = 0;
		}
		}*/
		ff = 0;
		cout << h << endl;
		s2 = new char[h - i];
		for ( ww = i; ww < h; ww++ )
		{
			file.read ( &s2[ff], 1 );
			ff++;
		}
		ww = i;
		cout << h - i << endl;
		cout << s2 << endl;
		i = 0;
		v = 0;
		fo = 0;
		ptravi = bin.phead;
		while ( v != ( h - ww ) )
		{
			for ( int k = 0; k <8; k++ )
			{
				t = s2[v] & ( m << k );
				p += t;
				std::bitset<8> x ( p );
				if ( x[voo] == 0 )
				{
					goal[fi] = '0';
				}
				else
				{
					goal[fi] = '1';
				}
				goal[fi + 1] = NULL;
				fi++;
				voo++;
				ptrav = sl4.phead;
				while ( ptrav != NULL )
				{
					fo = 0;
					while ( goal[fo] != NULL )
					{
						if ( goal[fo] != ptrav->zo[fo] )
						{
							flagu = 1;
							break;
						}
						fo++;
					}
					if ( ptrav->zo[fo] == NULL )
					{
						if ( flagu == 0 )
						{
							gooooool[cty] = ptrav->letter[0];
							gooooool[cty + 1] = NULL;
							cty++;
							fi = 0;
							for ( int yu = 0; goal[yu] != NULL; yu++ )
							{
								goal[yu] = NULL;
							}
							break;
						}
					}
					flagu = 0;
					ptrav = ptrav->pnext;
				}
			}
			int ooh = 0;
			if ( answer2 == 'Y' || answer2 == 'y' )
			{
				ooh = getascii ( s[v] );
				std::bitset<8> x ( p );
				std::cout << "the node is ( " << ooh << " ) which has the binary ( " << x << " )" << endl;
			}
			p = NULL;
			voo = 0;
			//ptravi = ptravi->pnext;
			v++;
			i++;
		}
	}
	cout << v << endl;
	answer2 = NULL;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "What do you want to see?" << endl;
	cout << "Do You Want To See The Compressed Scentence? [ y/n ]" << endl;
	cin >> answer2;
	if ( answer2 == 'Y' || answer2 == 'y' )
	{
		cout << "the compressed sentence is: " << endl;
		bin.dispall ( );
		cout << endl;
	}
	answer2 = NULL;
	if ( answer == 'C' || answer == 'c' || answer == 'B' || answer == 'b' )
	{
		cout << "Do You Want To See The Original Text? [y/n]" << endl;
		cin >> answer2;
		if ( answer2 == 'Y' || answer2 == 'y' )
		{
			cout << "the original sentence is: " << endl;
			cout << s << endl;
		}
	}
	answer2 = NULL;
	if ( answer == 'D' || answer == 'd' || answer == 'B' || answer == 'b' )
	{
		cout << "Do You Want To See The Decompressed Sentence? [y/n]" << endl;
		cin >> answer2;
		if ( answer2 == 'Y' || answer2 == 'y' )
		{
			cout << "the decomprsed sntence is: " << endl;
			cout << gooooool << endl;
		}
	}
	answer2 = NULL;
	cout << "Do You Want To See The Compressioon Ratio? [y/n]" << endl;
	cin >> answer2;
	if ( answer2 == 'Y' || answer2 == 'y' )
	{
		cout << "the number of characters before compression is ( " << noc << " ) character which equals ( " << no2 << " ) bit" << endl;
		cout << "the number of characters after compression is ( " << countingtimes << " ) character which equals ( " << no3 << " ) bit" << endl;
		cout << "the compression ratio is " << compression << " %" << endl;
	}
	answer2 = NULL;
	cout << endl;
}