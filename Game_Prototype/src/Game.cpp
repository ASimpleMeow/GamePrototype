#include <math.h>
#include "Game.h"
#include "game-imap/IMap.h"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600)) {
    //set up influencemap parameters
	m_player.SetInfluence(10);
    m_ePlayer.SetInfluence(-10);
     
    //Influence Map related
    sf::Vector2f anchorLoc(0,0);
    sf::Vector2u mapDim(32,32);
      
    m_ePlayer.SetPosition(sf::Vector2f(150,200));
    int tileSize=32;
    m_imap = std::make_shared<GameIMap::InfluenceMap>(mapDim.x,mapDim.y,anchorLoc.x,anchorLoc.y,tileSize);
    
    m_clock.restart();
    srand(time(nullptr));
     
	m_previousTime = m_clock.getElapsedTime();
    if (!m_map.load("resource/tileset_bw.png",sf::Vector2u(tileSize, tileSize), level, 32, 32))
        return ;
    
    if (!m_font.loadFromFile("resource/arial.ttf")) std::cout << "Error!!" << std::endl;

	m_window.GetRenderWindow()->setFramerateLimit(60);
}

Game::~Game(){}

Window* Game::GetWindow(){ return &m_window; }
sf::Time Game::GetElapsed() { return m_clock.getElapsedTime() - m_previousTime; }
void Game::RestartClock() { 
	m_previousTime += GetElapsed();
	m_clock.restart();
}

void Game::Update(){
    static int updateCounterIMap = 0;
	static sf::Vector2i oldPlayerPosition(0, 0);
	static sf::Vector2i old_E_PlayerPosition(0, 0);
    ++updateCounterIMap;
    m_window.Update();
	sf::Time deltaTime = m_clock.getElapsedTime() - GetElapsed();
	int intSpreadOutAmount = 5;
    
    m_player.Update(deltaTime.asSeconds());//use timeDelta, which needs to be calculated per frame
    m_ePlayer.Update(deltaTime.asSeconds());
    // Store the player position as it's used many times.
    if (updateCounterIMap%10==0){
		sf::Vector2i playerPosition = m_map.GetActualTileLocation(m_player.GetPosition());
        sf::Vector2i  ePlayerPosition = m_map.GetActualTileLocation(m_ePlayer.GetPosition());
        
		if (oldPlayerPosition != playerPosition || old_E_PlayerPosition != ePlayerPosition) {
			m_imap->clear();//everytime player moves to new tile, reset influencemap calculation
			m_imap->setCellValue(playerPosition.x, playerPosition.y, m_player.GetInfluence());
			m_imap->setCellValue(ePlayerPosition.x, ePlayerPosition.y, m_ePlayer.GetInfluence());
			m_imap->propValue(0.1, GameIMap::PropCurve::Linear);
			//both player and enemys need to be updated as imap has been cleared at start
			m_imap->propagateInfluence(playerPosition.x, playerPosition.y, intSpreadOutAmount, GameIMap::PropCurve::Linear);
			m_imap->propagateInfluence(ePlayerPosition.x, ePlayerPosition.y, intSpreadOutAmount, GameIMap::PropCurve::Linear, -1.0f);

		}
        
        if (m_window.IsDebug() && updateCounterIMap%1000==0)
			cout << "enemy imap val at position =" << m_imap->getCellValue(ePlayerPosition.x,ePlayerPosition.y)<< endl;
        oldPlayerPosition=playerPosition;
        old_E_PlayerPosition=ePlayerPosition;
        
    }
}
sf::Text Game::utilityFn(float val, sf::Vector2i pos) {
    std::stringstream stream;
    stream << fixed <<setprecision(1) <<val;
    string s = stream.str();
    
    sf::Text sfTxt;
    
    sfTxt.setString(s);
    sfTxt.setFont(m_font);
    sfTxt.setCharacterSize(10);//magic number - change based on tilesize
    sfTxt.setFillColor(sf::Color::Black);
    
    sf::Vector2f text_pos;
    text_pos= m_map.GetActualTileLocation(pos.x,pos.y);
    
    sfTxt.setPosition(text_pos);
    return sfTxt;
}

void Game::Render() {
	auto clamp = [=](float x, float l, float h) {
		if (x < l) return l;
		if (x > h) return h;
		return x;
	};

	auto smoothstep = [=](float edge0, float edge1, float x) {
		x = clamp((x - edge0) / (edge1 - edge0), 0, 1);
		return x * x * (3 - 2 * x);
	};

	sf::Time deltaTime = m_clock.getElapsedTime() - GetElapsed();

    m_window.BeginDraw();
    m_window.GetRenderWindow()->draw(this->m_map);

    std::vector<sf::Text> sfTextArr;
    for (auto j=0;j<m_imap->m_iHeight;j++ )
        for (auto i =0; i< m_imap->m_iWidth;i++){
			sf::Color color = sf::Color::Black;
			auto cellValue = m_imap->getCellValue(j, i);
			auto isPlayer = cellValue > 0;
			if (cellValue != 0) {
				cellValue = 255 - (smoothstep(-3, 6, abs(cellValue)) * 255);
				if (isPlayer) color.r = clamp(cellValue, 50, 255);
				else color.b = clamp(cellValue, 50, 255);
			} else color = sf::Color::White;
            m_map.rectangeOnTile(sf::Vector2i(i,j),color );

			if (m_window.IsDebug()) sfTextArr.push_back(utilityFn(m_imap->getCellValue(j, i),sf::Vector2i(j,i)) );
        }
    
    m_map.printOnTileArr(sfTextArr);
	m_player.Draw(*m_window.GetRenderWindow(), deltaTime.asSeconds());
    m_ePlayer.SetEvilState();
    m_ePlayer.Draw(*m_window.GetRenderWindow(), deltaTime.asSeconds());
    m_window.EndDraw();
}
