#pragma once
#include <wx/wx.h>
#include <wx/tokenzr.h>

enum Variant
{
	ID_CEZAR = 1,
	ID_VIGENERE,
	ID_RSA
};

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	bool encrypt, needkey;
	short key;
	char message;
	long intermediate;
	long long public_key_e, private_key_d, module_n;
	std::string transformedText, keyWord;
	std::vector<long long> encryptedMessage;

	Variant cipher;

	wxString savedText, intermediateText, result;
	wxPanel* panel;

	wxStaticText* headlineText;
	wxTextCtrl* inputText;

	wxButton* buttonEncrypt;
	wxButton* buttonDecrypt;
	wxButton* nextButton;
	wxButton* buttonCaesars;
	wxButton* buttonVigenere;
	wxButton* buttonRSA;

	void OnEncryptButtonEvent(wxCommandEvent& evt);
	void OnDecryptButtonEvent(wxCommandEvent& evt);
	void ShowChoiceCipher();
	void OnCaesarsButtonEvent(wxCommandEvent& evt);
	void OnVigenereButtonEvent(wxCommandEvent& evt);
	void OnRSAButtonEvent(wxCommandEvent& evt);
	void CreateHeader(const wxString& header);
	void CreateWindowWithInputText(void(MainFrame::* name)(wxCommandEvent&),
		const wxString& FirstHeader, const wxString& SecondHeader);
	void EnDecryptedWord(wxCommandEvent& evt);
	void GetKeyCeaserAndVigenere(wxCommandEvent& evt);
	void RSAInputKey(wxCommandEvent& evt);
	void CreateResultWindow(const wxString& word);
	void GetNValueRsa(wxCommandEvent& evt);
	wxButton* CreateAndBindButton(void(MainFrame::* name)(wxCommandEvent&),
		const wxString& text, short length_box=150, short wide_box=50);
};

