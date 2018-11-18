#include <math.h>
#include "Game.h"
#include "game-imap/IMap.h"

Game::Game() : m_window("Tiling", sf::Vector2u(1280, 800))

{
    
    
    //set up influencemap parameters
    m_player.setInfluence(10);
    m_ePlayer.setInfluence(-2);
    
    
    //Influence Map related
    sf::Vector2f anchorLoc(0,0);
    sf::Vector2u mapDim(32,32);
    
    
    m_ePlayer.SetPosition(sf::Vector2f(150,200));
    int tileSize=32;
    m_imap = std::make_shared<GameIMap::InfluenceMap>(mapDim.x,mapDim.y,anchorLoc.x,anchorLoc.y,tileSize);
    
    
    
    m_clock.restart();
    srand(time(nullptr));
    
    
    m_elapsed = 0.0f;
    if (!m_map.load("resource/tileset_bw.png",sf::Vector2u(tileSize, tileSize), level, 32, 32))
        return ;
    
    if (!m_font.loadFromFile("resource/arial.ttf"))
    {
        // Error...
        std::cout <<"Error!!"<<std::endl;
        
    }

	m_window.GetRenderWindow()->setFramerateLimit(60);
    
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &m_window; }



void Game::Update(){
    static int updateCounterIMap =0;
    static sf::Vector2i oldPlayerPosition(0,0);
    static sf::Vector2i old_E_PlayerPosition(0,0);
    ++updateCounterIMap;
    m_window.Update();
    float currentTime = m_clock.restart().asSeconds();
    float timeDelta = 0.f;
    sf::Event event;
    float newTime = m_clock.getElapsedTime().asSeconds();
    float frameTime = std::max(0.f, newTime - currentTime);
    
    
    m_player.Update(0.01);//use timeDelta, which needs to be calculated per frame
    m_ePlayer.Update(0.01);
    // Store the player position as it's used many times.
    if (updateCounterIMap%10==0){
        sf::Vector2i playerPosition = m_map.GetActualTileLocation(m_player.GetPosition());
        sf::Vector2i  ePlayerPosition = m_map.GetActualTileLocation(m_ePlayer.GetPosition());
        
        if(oldPlayerPosition!=playerPosition){
            m_imap->clear();//everytime player moves to new tile, reset influencemap calculation
            m_imap->setCellValue(playerPosition.x,playerPosition.y, 30);//m_player.getInfluence());
            
            m_imap->propValue(0.1, GameIMap::PropCurve::Linear);
            //both player and enemys need to be updated as imap has been cleared at start
            for (auto i = 0; i < 2; i++)
            {
                int  intSpreadOutAmount=5;
                m_imap->propagateInfluence(playerPosition.x,playerPosition.y, intSpreadOutAmount, GameIMap::PropCurve::Linear);
                m_imap->propagateInfluence(ePlayerPosition.x,ePlayerPosition.y, intSpreadOutAmount, GameIMap::PropCurve::Linear);
            }
            
        }
        
        //if enemy position changes, update influence map
        if(old_E_PlayerPosition!=ePlayerPosition){
            m_imap->clear();//if not done here,
            m_imap->setCellValue(ePlayerPosition.x,ePlayerPosition.y,m_ePlayer.getInfluence());
            m_imap->propValue(0.1, GameIMap::PropCurve::Linear);
            
            //both player and enemys need to be updated as imap has been cleared at start
            for (auto i = 0; i < 2; i++)
            {
                
                int intSpreadOutAmount=5;
                m_imap->propagateInfluence(playerPosition.x,playerPosition.y, intSpreadOutAmount, GameIMap::PropCurve::Linear);
                m_imap->propagateInfluence(ePlayerPosition.x,ePlayerPosition.y, intSpreadOutAmount, GameIMap::PropCurve::Linear);
            }
            
        }
        
        
        
        if (updateCounterIMap%1000==0)
            cout << "enemy imap val at position =" << m_imap->getCellValue(ePlayerPosition.x,ePlayerPosition.y)<< endl;
        
        // m_imap->propagateInfluence(ePlayerPosition.x, ePlayerPosition.y, 3, GameIMap::PropCurve::Linear);
        oldPlayerPosition=playerPosition;
        old_E_PlayerPosition=ePlayerPosition;
        
    }
    
    // if (updateCounterIMap%100==0)
    
    
    currentTime = newTime;
    
    //    float timestep = 1.0f / m_snake.GetSpeed();
    //    if(m_elapsed >= timestep){
    //
    //
    //        m_elapsed -= timestep;
    //
    //    }
}
sf::Text Game::utilityFn(float val, sf::Vector2i pos)
{
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
void Game::Render(){
	sf::Color color = sf::Color::White;
	auto sigmoid = [=](int v) { return exp(v) / (exp(v) + 1); };

    m_window.BeginDraw();
    // Render here.
    m_window.GetRenderWindow()->draw(this->m_map);
    // Draw the player.
    m_player.Draw(*m_window.GetRenderWindow(), m_player.m_timeDelta);
    
    std::stringstream stream;
    stream << fixed <<setprecision(1) <<m_player.getInfluence();
    string s = stream.str();
    std::vector<sf::Text> sfTextArr;
    sf::Vector2f location;
    for (auto j=0;j<m_imap->m_iHeight;j++ )
        for (auto i =0; i< m_imap->m_iWidth;i++){
            location=m_map.GetActualTileLocation(j,i);
            
			auto val = sigmoid(m_imap->getCellValue(j, i));
			color.r = 255;
			color.g = 255 * ((1 - val) < 0.1 ? 0 : (1-val)*2);
			color.b = color.g;
            m_map.rectangeOnTile(sf::Vector2i(i,j),color );

			if (m_window.IsDebug())
				sfTextArr.push_back(utilityFn(m_imap->getCellValue(j, i),sf::Vector2i(j,i)) );
        }
    
    
    
    m_map.printOnTileArr(sfTextArr);
    m_ePlayer.setEvilState();
    m_ePlayer.Draw(*m_window.GetRenderWindow(), m_player.m_timeDelta);
    m_window.EndDraw();
}
