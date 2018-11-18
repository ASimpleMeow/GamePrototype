
#ifndef Object_h
#define Object_h

class Object
{
public:
    /**
     * Default constructor.
     */
    Object();
    
    void setInfluence(float influence){m_influenceValue=influence;};
    float getInfluence(){ return(m_influenceValue);};
    virtual void Update(float timeDelta) {};
    virtual void Draw(sf::RenderWindow &window, float timeDelta);
    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition() const;
    bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
    sf::Sprite& GetSprite();
    int GetFrameCount() const;
    bool IsAnimated();
    void SetAnimated(bool isAnimated);
    
protected:
    
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    
private:
    
   
    void NextFrame();
    
private:
    
    float m_influenceValue;
    int m_animationSpeed;
    bool m_isAnimated;
    int m_frameCount;
    int m_currentFrame;
    int m_frameWidth;
    int m_frameHeight;
public:
    float m_timeDelta;
};

#endif /* Object_h */
