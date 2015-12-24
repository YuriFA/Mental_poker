#pragma comment(lib, "crypt32.lib")
#include <iostream>
#include <time.h>
#include "Player.h"

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define PASSWORD_LENGTH 512

using namespace std;

void MyHandleError(char *s);

Player::Player(){
	//this->gen_k();
	this->Init();
}

Player::~Player(){
	if (this->m_hKey)   {CryptDestroyKey(this->m_hKey);}
    if (this->m_hProv)  {CryptReleaseContext(this->m_hProv, 0);}
}

void Player::showCards(){
	deck.show();
}

void _stdcall Player::encryptData(){
	BYTE *pbBuffer = (BYTE*)"PASSWORD";
	DWORD               dwDataSz        = strlen((char *)pbBuffer)+1;
	DWORD               dwBufSz         = dwDataSz;
	BYTE                *pbtData        = new BYTE[dwBufSz];

    memcpy(pbtData, (BYTE *)"PASSWORD", dwDataSz);

	if (CryptEncrypt(this->m_hKey, 0, FALSE, 0, pbtData, &dwDataSz, dwBufSz)) // FALSE или TRUE в качестве флага последнего роли не играют 
    { 
        printf("encrypted!\n"); 
    } 
    else 
    { 
        printf("error, %X!\n", GetLastError()); // NTE_BAD_LEN 
    }
}

void Player::encryptCards(){
	//Player::deck.encDeck();
}

void Player::Init(){
	
	HCRYPTPROV hProv;	
	DWORD dwBlobLen;	
	BYTE *pbKeyBlob;   

	if (CryptAcquireContext(&this->m_hProv, NULL, NULL, PROV_RSA_FULL, 0))
    {
        HCRYPTHASH hHash;
		CHAR szPassword[PASSWORD_LENGTH] = "password";
		DWORD dwLength;
		dwLength = (DWORD) strlen(szPassword);
        if (CryptCreateHash(this->m_hProv, CALG_MD5, 0, 0, &hHash))
        {
            if (CryptHashData(hHash, (BYTE *)szPassword, dwLength, 0))
            {
                if(!CryptDeriveKey(this->m_hProv, CALG_3DES, hHash, CRYPT_EXPORTABLE, &this->m_hKey))
				{
					MyHandleError("Error CryptDeriveKey");
				}
            }
			else
			{
				MyHandleError("Error CryptHashData");
			}
            CryptDestroyHash(hHash);
        }
		else
		{
			MyHandleError("Error CryptCreateHash");
		}
    }
	else 
	{
		MyHandleError("Error CryptAcquireContext");
	}

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
	if(CryptGetUserKey(
		hProv,
		AT_SIGNATURE,
		&hKey))
	{
        printf("The signature key has been acquired. \n");
    }
    else
    {
        MyHandleError("Error during CryptGetUserKey for signkey.");
    }

	//if(CryptGenKey(
	//		  hProv, 
	//		  AT_SIGNATURE, 
	//		  512 << 16 | CRYPT_EXPORTABLE, 
	//		  &hKey))
	// {
	//		 printf("A session key has been created.\n");
	//		 
	// } 
	// else
	// {
	//		  printf("Error during CryptGenKey.\n"); 
	//		  //exit(1);
	// }

	if(CryptExportKey(   
	   hKey,    
	   NULL,    
	   PUBLICKEYBLOB,
	   0,    
	   NULL, 
	   &dwBlobLen)) 
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

	if(CryptGetUserKey(   
        hProv,    
        AT_SIGNATURE,    
        &hKey)) 
    {
        printf("The signature key has been acquired. \n");
    }
    else
    {
        MyHandleError("Error during CryptGetUserKey for signkey.");
    }

	if(CryptCreateHash( hProv, CALG_MD5, 0, 0, &hHash)) 
	{
		 printf("Hash object created. \n");
		 //cout<<"\n"<<hProv<<"\n";
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

	dwSigLen = 0;
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

	if(CryptSignHash( hHash, AT_SIGNATURE/*AT_KEYEXCHANGE*/, NULL, 0, NULL, &dwSigLen)) 
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

	//-------------------------------------------------------------------
	// Create a new hash object.

	if(CryptImportKey(
		hProv,
		pbKeyBlob,
		dwBlobLen,
		0,
		0,
		&hPubKey))
	{
			printf("The key has been imported.\n");
	}
	else
	{
			MyHandleError("Public key import failed.");
	}
	//-------------------------------------------------------------------
	// Create a new hash object.

	cout<<"\n"<<hPubKey<<"\n";

	if(CryptCreateHash(
		hProv, 
		CALG_MD5, 
		0, 
		0, 
		&hHash)) 
	{
			printf("The hash object has been recreated. \n");
	}
	else
	{
			MyHandleError("Error during CryptCreateHash.");
	}
	//-------------------------------------------------------------------
	// Compute the cryptographic hash of the buffer.

	if(CryptHashData(
		hHash, 
		pbBuffer, 
		dwBufferLen, 
		0)) 
	{
			printf("The new hash has been created.\n");
	}
	else
	{
			MyHandleError("Error during CryptHashData.");
	}
	//-------------------------------------------------------------------
	// Validate the digital signature.

	if(CryptVerifySignature(
		hHash, 
		pbSignature, 
		dwSigLen, 
		hPubKey,
		NULL, 
		0)) 
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
		//  End of main
}

void MyHandleError(char *s)
{
    fprintf(stderr,"\nAn error occurred in running the program. \n");
    fprintf(stderr,"%s\n",s);
    fprintf(stderr, "Error number %x.\n", GetLastError());
    fprintf(stderr, "Program terminating. \n\n");
    //exit(1);
} // End of MyHandleError