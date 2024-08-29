#include "MainFrame.h"
#include "Crypto.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(500, 300)){
	panel = new wxPanel(this);
	
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	CreateHeader("Choose action");
	vbox->Add(headlineText, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 50);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

	buttonEncrypt = CreateAndBindButton(&MainFrame::OnEncryptButtonEvent, "Encrypt");
	buttonDecrypt = CreateAndBindButton(&MainFrame::OnDecryptButtonEvent, "Decrypt");

	hbox->Add(buttonEncrypt, 0, wxRIGHT, 20);
	hbox->Add(buttonDecrypt, 0);
	vbox->Add(hbox, 0, wxALIGN_CENTER_HORIZONTAL);

	panel->SetSizer(vbox);
}

void MainFrame::OnEncryptButtonEvent(wxCommandEvent& evt){
	encrypt = true;
	ShowChoiceCipher();
}

void MainFrame::OnDecryptButtonEvent(wxCommandEvent& evt){
	encrypt = false;
	ShowChoiceCipher();
}

void MainFrame::ShowChoiceCipher(){
	panel->DestroyChildren();
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	CreateHeader(encrypt ? "Choose your method of encryption" : "Choose your method of decryption");
	vbox->Add(headlineText, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 50);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	
	buttonCaesars = CreateAndBindButton(&MainFrame::OnCaesarsButtonEvent, "Caesars");
	buttonVigenere = CreateAndBindButton(&MainFrame::OnVigenereButtonEvent, "Vigenere");
	buttonRSA = CreateAndBindButton(&MainFrame::OnRSAButtonEvent, "RSA");
	
	hbox->Add(buttonCaesars, 0, wxRIGHT, 15);
	hbox->Add(buttonVigenere, 0, wxRIGHT, 15);
	hbox->Add(buttonRSA, 0);
	vbox->Add(hbox, 0, wxALIGN_CENTER_HORIZONTAL);

	panel->SetSizer(vbox);
	panel->Layout();
}

void MainFrame::OnCaesarsButtonEvent(wxCommandEvent& evt){
	cipher = ID_CEZAR;
	needkey = true;
	CreateWindowWithInputText(&MainFrame::EnDecryptedWord, 
		"Write message you want to encrypt", "Write message you want to decrypt");
}

void MainFrame::OnVigenereButtonEvent(wxCommandEvent& evt){
	cipher = ID_VIGENERE;
	needkey = true;
	CreateWindowWithInputText(&MainFrame::EnDecryptedWord,
		"Write message you want to encrypt", "Write message you want to decrypt");
}

void MainFrame::OnRSAButtonEvent(wxCommandEvent& evt){
	cipher = ID_RSA;
	needkey = false;
	CreateWindowWithInputText(&MainFrame::EnDecryptedWord,
		"Write message you want to encrypt", "Write message you want to decrypt");
}

void MainFrame::CreateHeader(const wxString& header){
	headlineText = new wxStaticText(panel, wxID_ANY, header, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	headlineText->SetFont(font);
}

void MainFrame::CreateWindowWithInputText(void(MainFrame::* name)(wxCommandEvent&), const wxString& FirstHeader, const wxString& SecondHeader = " ")
{
	panel->DestroyChildren();
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	CreateHeader((SecondHeader=="" || ID_RSA && intermediateText != "") ? (FirstHeader) :
		(encrypt ? FirstHeader : SecondHeader));
		
	vbox->Add(headlineText, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 50);
	vbox->AddStretchSpacer(1);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

	inputText = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, 25));
	nextButton = CreateAndBindButton(name, "-->",50,25);

	hbox->Add(inputText, 0, wxRIGHT, 20);
	hbox->Add(nextButton, 0);
	vbox->Add(hbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	vbox->AddStretchSpacer(2.5);

	panel->SetSizer(vbox);
	panel->Layout();
}

void MainFrame::EnDecryptedWord(wxCommandEvent& evt) {
	savedText = inputText->GetValue();
	if (savedText.IsEmpty())
	{
		wxLogMessage("You not enter a message");
	}
	else {
		needkey ? CreateWindowWithInputText
		(&MainFrame::GetKeyCeaserAndVigenere, cipher == ID_VIGENERE? "Enter the keyword" : "Enter the key" , "") :
		CreateWindowWithInputText(&MainFrame::RSAInputKey, "Enter public key (e)", "Enter private key (d)");
	}
}

void MainFrame::GetKeyCeaserAndVigenere(wxCommandEvent& evt){
	intermediateText =  inputText->GetValue();
	if (ID_CEZAR&& intermediateText.ToLong(&intermediate)){
		key = static_cast<short>(intermediate);
		transformedText = savedText.ToStdString();
		savedText = ProcessStringForCezar(transformedText, key, encrypt);
		CreateResultWindow(savedText);
	}
	else if (ID_VIGENERE)
	{
		transformedText = savedText.ToStdString();
		keyWord = intermediateText.ToStdString();
		if (keyWord.empty())
			wxLogError("Empty string");
		savedText = Vigenere(transformedText, keyWord, encrypt);
		CreateResultWindow(savedText);
	}
	else
		wxLogError("Invalid key");
}

void MainFrame::RSAInputKey(wxCommandEvent& evt){
	intermediateText = inputText->GetValue();
	encrypt ? intermediateText.ToLongLong(&public_key_e) : intermediateText.ToLongLong(&private_key_d);
	CreateWindowWithInputText(&MainFrame::GetNValueRsa, "Enter a module (n): ");
}

void MainFrame::GetNValueRsa(wxCommandEvent& evt)
{
	intermediateText = inputText->GetValue();
	intermediateText.ToLongLong(&module_n);
	if (encrypt)
		if (public_key_e && module_n)
		{
			transformedText = savedText.ToStdString();
			encryptedMessage = EncryptionRSA(transformedText, 
				static_cast<long>(public_key_e), static_cast<long>(module_n));
			
			for (long long n : encryptedMessage)
			{
				result += wxString::Format("%lld ", n);
			}
			CreateResultWindow(result);
		}
		else
		{
			wxLogMessage("Empty key or module");
		}
	else
	{
		if (private_key_d && module_n)
		{
			wxStringTokenizer tokenizer(savedText, " ");
			while (tokenizer.HasMoreTokens()){
				long long num;
				if (tokenizer.GetNextToken().ToLongLong(&num))
				{
					encryptedMessage.push_back(num);
				}
				wxString decryptedMessage = DecryptionRSA(encryptedMessage, private_key_d, module_n);
				CreateResultWindow(decryptedMessage);
			}
		}
		else
			wxLogMessage("Empty ker or module");
	}
}

void MainFrame::CreateResultWindow(const wxString& word)
{
	panel->DestroyChildren();

	CreateHeader(word);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	vbox->AddSpacer(105);
	vbox->Add(headlineText, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	vbox->AddSpacer(105);

	panel->SetSizer(vbox);
	panel->Layout();
}

wxButton* MainFrame::CreateAndBindButton(void(MainFrame::* name)(wxCommandEvent&),
	const wxString& text, short length_box, short wide_box)
{
	wxButton* button = new wxButton(panel, wxID_ANY, text, wxDefaultPosition, wxSize(length_box, wide_box));
	button->Bind(wxEVT_BUTTON, name, this);
	return button;
}