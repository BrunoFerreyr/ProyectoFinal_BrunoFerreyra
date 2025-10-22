#include "ButtonAsset.h"
ButtonAsset::ButtonAsset(AssetData assetData, sf::Font& font,const std::string& buttonName, std::function<void()> func)
	: Asset(assetData)
{
	onClickEvent = func;
	buttonText = new sf::Text(font,buttonName,24);
	// Configurar el texto del botón (fuente, tamaño, color, etc.)
	//buttonText.setFont(...); // Asignar una fuente válida
	buttonText->setFillColor(sf::Color::Black); 
	// Color del texto
	// Centrar el texto en el botón
	sf::FloatRect textBounds = buttonText->getLocalBounds();
	buttonText->setOrigin({textBounds.size.x * 0.5f,
		textBounds.size.y *0.5f });
	buttonText->setPosition({assetData.position.x + (assetData.size.size.x * 0.5f) ,assetData.position.y + (assetData.size.size.y * 0.5f)});
}
ButtonAsset::~ButtonAsset()
{
	delete buttonText;
}
void ButtonAsset::OnClickEvent()
{
	if (onClickEvent)
	{
		onClickEvent();
	}
}
sf::Text* ButtonAsset::GetText()
{
	return buttonText;
}