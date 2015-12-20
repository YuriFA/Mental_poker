#pragma comment(lib, "crypt32.lib")
#include <iostream>
#include <time.h>
#include "Player.h"
#include <Windows.h>
#include <wincrypt.h>

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

using namespace std;

void MyHandleError(char *s);

Player::Player(){
	this->gen_k();
}

void Player::showCards(){
	cards.show();
}

void Player::encryptCards(){
	Player::cards.encDeck();
}

void Player::gen_k(){	

	HCRYPTPROV hProv;
	BYTE *pbBuffer= (BYTE *)"The data that is to be hashed and signed.";
	DWORD dwBufferLen = strlen((char *)pbBuffer)+1;
	HCRYPTHASH hHash;
	HCRYPTKEY hKey;
	HCRYPTKEY hPubKey;
	BYTE *pbKeyBlob;        
	BYTE *pbSignature;
	DWORD dwSigLen;
	DWORD dwBlobLen;

	//-------------------------------------------------------------------
	// Acquire a cryptographic provider context handle.

	if(CryptAcquireContext( &hProv, NULL, NULL, PROV_RSA_FULL, 0)) 
	{
		 printf("CSP context acquired.\n");
	}
	else
	{
		 MyHandleError("Error during CryptAcquireContext.");
	}

	if(CryptGetUserKey( hProv, AT_SIGNATURE, &hKey)) 
	{
		printf("The signature key has been acquired. \n");
	}
	else
	{
		MyHandleError("Error during CryptGetUserKey for signkey.");
	}
	if(CryptExportKey( hKey, NULL, PUBLICKEYBLOB, 0, NULL, &dwBlobLen)) 
	{
		 printf("Size of the BLOB for the public key determined. \n");
	}
	else
	{
		 MyHandleError("Error computing BLOB length.");
	}
	//-------------------------------------------------------------------
	// Allocate memory for the pbKeyBlob.

	if(pbKeyBlob = (BYTE*)malloc(dwBlobLen)) 
	{
		printf("Memory has been allocated for the BLOB. \n");
	}
	else
	{
		MyHandleError("Out of memory. \n");
	}
	//-------------------------------------------------------------------
	// Do the actual exporting into the key BLOB.

	if(CryptExportKey( hKey, NULL, PUBLICKEYBLOB, 0, pbKeyBlob, &dwBlobLen))
	{
		 printf("Contents have been written to the BLOB. \n");
	}
	else
	{
		MyHandleError("Error during CryptExportKey.");
	}
	//-------------------------------------------------------------------
	// Create the hash object.

	if(CryptCreateHash( hProv, CALG_MD5, 0, 0, &hHash)) 
	{
		 printf("Hash object created. \n");
	}
	else
	{
		MyHandleError("Error during CryptCreateHash.");
	}
	//-------------------------------------------------------------------
	// Compute the cryptographic hash of the buffer.

	if(CryptHashData( hHash, pbBuffer, dwBufferLen, 0)) 
	{
		 printf("The data buffer has been hashed.\n");
	}
	else
	{
		 MyHandleError("Error during CryptHashData.");
	}
	//-------------------------------------------------------------------
	// Determine the size of the signature and allocate memory.

	dwSigLen= 0;
	if(CryptSignHash( hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen)) 
	{
		 printf("Signature length %d found.\n",dwSigLen);
	}
	else
	{
		 MyHandleError("Error during CryptSignHash.");
	}
	//-------------------------------------------------------------------
	// Allocate memory for the signature buffer.

	if(pbSignature = (BYTE *)malloc(dwSigLen))
	{
		 printf("Memory allocated for the signature.\n");
	}
	else
	{
		 MyHandleError("Out of memory.");
	}
	//-------------------------------------------------------------------
	// Sign the hash object.

	if(CryptSignHash( hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)) 
	{
		 printf("pbSignature is the hash signature.\n");
	}
	else
	{
		 MyHandleError("Error during CryptSignHash.");
	}
	//-------------------------------------------------------------------
	// Destroy the hash object.

	if(hHash) 
	  CryptDestroyHash(hHash);

	printf("The hash object has been destroyed.\n");
	printf("The signing phase of this program is completed.\n\n");	

	if(CryptImportKey( hProv, pbKeyBlob, dwBlobLen, 0, 0, &hPubKey))
	{
		 printf("The key has been imported.\n");
	}
	else
	{
		 MyHandleError("Public key import failed.");
	}
	//-------------------------------------------------------------------
	// Create a new hash object.

	if(CryptCreateHash( hProv, CALG_MD5, 0, 0, &hHash)) 
	{
		 printf("The hash object has been recreated. \n");
	}
	else
	{
		 MyHandleError("Error during CryptCreateHash.");
	}
	//-------------------------------------------------------------------
	// Compute the cryptographic hash of the buffer.

	if(CryptHashData( hHash, pbBuffer, dwBufferLen, 0)) 
	{
		 printf("The new hash has been created.\n");
	}
	else
	{
		 MyHandleError("Error during CryptHashData.");
	}
	//-------------------------------------------------------------------
	// Validate the digital signature.

	if(CryptVerifySignature( hHash, pbSignature, dwSigLen, hPubKey, NULL, 0)) 
	{
		 printf("The signature has been verified.\n");
	}
	else
	{
		 printf("Signature not validated!\n");
	}
	//-------------------------------------------------------------------
	// Free memory to be used to store signature.

	if(pbSignature)
	  free(pbSignature);

	//-------------------------------------------------------------------
	// Destroy the hash object.

	if(hHash) 
	  CryptDestroyHash(hHash);

	//-------------------------------------------------------------------
	// Release the provider handle.

	if(hProv) 
	   CryptReleaseContext(hProv, 0);
}

void MyHandleError(char *s)
{
    fprintf(stderr,"An error occurred in running the program. \n");
    fprintf(stderr,"%s\n",s);
    fprintf(stderr, "Error number %x.\n", GetLastError());
    fprintf(stderr, "Program terminating. \n");
    //exit(1);
} // End of MyHandleError