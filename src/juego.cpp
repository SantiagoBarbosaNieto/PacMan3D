    #include <iostream>
    #include "juego.h"
    #include "pacman.h"

    Juego::Juego()
    {
        std::string filename[5] = {"../assets/index.bmp", "../assets/t2.bmp", "../assets/t3.bmp", "../assets/t4.bmp", "../assets/t5.bmp"}; // 2 texturas nuevas agregadas
        for ( int i = 0; i < 5; i++ )
        {
            this->m_Texturas.push_back(loadTextureFromFile ((filename[ i ])));
            //std::cout<<"Tex: " << this->m_Texturas[i] <<"\n";
        }
        this->buildBlocks();
        this->buildCoins();
        this->buildGhosts();
        this->m_Pacman = new Pacman();
        Vec3 pos = {playerSpawn.x, m_Pacman->getPos().y, playerSpawn.y};
        m_Pacman->setPos(pos);
	
        this->buildPowerUps();
    }
    Juego::~Juego()
    {
        
    }
    void Juego::setPos(float x, float y, float z)
    {
        Vec3 aux = this->m_Pos;
        this->m_Pos = {x,y,z};
        aux = {x-aux.x, y-aux.y, z-aux.z};
        for(Block b: this->m_Paredes)
        {
            b.updatePos(aux);
        }
    }

    void Juego::setPos(Vec3 pos)
    {
        Vec3 aux = this->m_Pos;
        this->m_Pos = pos;
        aux = {pos.x-aux.x, pos.y-aux.y, pos.z-aux.z};
        for(Block b: this->m_Paredes)
        {
            b.updatePos(aux);
        }
    }

    std::vector<Block> Juego::getParedes()
    {
        return this->m_Paredes;
    }

    std::vector<Coin*> Juego::getCoins()
    {
        return this->m_Coins;
    }

    void Juego::buildCoins()
    {
        for(int i = 0; i < this->m_MapRows; i++)
        {
            for(int j = 0; j < this->m_MapCols; j++)
            {
                int id = this->m_Map[i][j];
                if(id == this->m_IdCoin)
                {
                    Coin* c = new Coin();
                    c->setPos({this->m_Pos.x + float(i), this->m_Pos.y + 0.0f, this->m_Pos.z + float(j) });

                    this->m_Coins.push_back(c);
                }
            }
        }
        std::cout << "Build coins succeeded" << std::endl;
    }

    std::vector<PowerUp*> Juego::getPowerUps() {
        return this->m_PowerUps;
    }

    void Juego::buildPowerUps(){
        for(int i = 0; i < this->m_MapRows; i++)
        {
            for(int j = 0; j < this->m_MapCols; j++)
            {
                int id = this->m_Map[i][j];
                if(id == this->m_IdPower)
                {
                    PowerUp* p = new PowerUp();
                    p->setPos({this->m_Pos.x + float(i), this->m_Pos.y + 0.0f, this->m_Pos.z + float(j) });

                    this->m_PowerUps.push_back(p);
                }
            }
        }
        std::cout << "Build PowerUps succeeded" << std::endl;
    }

    void Juego::increaseCoins(int amount) {
        this->coinCounter += amount;
    }

    int Juego::getCoinCount(){
        return this->coinCounter;
    }

    void Juego::buildBlocks()
    {
        for(int i = 0; i < this->m_MapRows; i++)
        {
            for(int j = 0; j < this->m_MapCols; j++)
            {
                
                int id = this->m_Map[i][j];
                if(id == this->m_IdPLayerSpawn)
                {
                    playerSpawn = {(float)i,(float)j};
                }
                if(id == this->m_IdPared)
                {
                    Block* b = new Block();
                    b->setPos({this->m_Pos.x + float(i), this->m_Pos.y + 0.0f, this->m_Pos.z + float(j) });
                    b->setTextures(this->m_Texturas);
                    Vec3 pos = b->getPos();
                    bool top = false;
                    bool bottom =false;
                    bool front = false;
                    bool back = false;
                    bool right = false;
                    bool left = false;

                    int x = pos.x + 1 -m_Pos.x;
                    int y = pos.z+0 -m_Pos.z;
                    if(x >= 0 && x < 31)
                    {
                        if(m_Map[x][y] == 1)
                        {
                            front = true;
                        }
                    }
                    x = pos.x - 1 -m_Pos.x;
                    y = pos.z+0 -m_Pos.z;
                    if(x >= 0 && x < 31)
                    {
                        if(m_Map[x][y] == 1)
                        {
                            back = true;
                        }
                    }
                    x = pos.x -m_Pos.x;
                    y = pos.z+-1 -m_Pos.z;
                    if(y >= 0 && y < 28)
                    {
                        if(m_Map[x][y] == 1)
                        {
                            left = true;
                        }
                    }
                    x = pos.x -m_Pos.x;
                    y = pos.z+1 -m_Pos.z;
                    if(y >= 0 && y < 28)
                    {
                        if(m_Map[x][y] == 1)
                        {
                            right = true;
                        }
                    }
                    b->setFaceCull(right, left, bottom, top, front, back);
                    

                    this->m_Paredes.push_back(*b);
                }
            }
        }
        std::cout << "Build walls succeeded" << std::endl;
    }

    void Juego::buildGhosts(){
        int Gid = 0;
        for(int i = 0; i < this->m_MapRows; i++)
        {
            for(int j = 0; j < this->m_MapCols; j++)
            {
                int id = this->m_Map[i][j];
                if(id == this->m_IdGhostSpawn)
                {
                    Ghost* g = new Ghost();
                    g->setPos({this->m_Pos.x + float(i), this->m_Pos.y + 0.0f, this->m_Pos.z + float(j) });
                    g->setId(Gid);
                    g->setInitialPos(g->getPos());
                    //std::cout<<"Ghost id " << Gid <<"\n"; 
                    Gid++;
                    this->m_Ghosts.push_back(g);
                }
            }
        }
    }

    void Juego::draw()
    {
        for(int i = 0; i < this->m_Paredes.size(); i++)
        {
            this->m_Paredes[i].draw();
            
        }

        for(int i = 0; i < this->m_Coins.size(); i++) {
            if(this->m_Coins[i]->isActive())
            {   glPushMatrix();
                this->m_Coins[i]->draw();
                glPopMatrix();
            }
        }

        for(int i = 0; i < this->m_PowerUps.size(); i++) {
            if(this->m_PowerUps[i]->isActive())
            {
                this->m_PowerUps[i]->draw();
            }
        }
        
        this->m_Pacman->draw();

        for(int i = 0; i < this->m_Ghosts.size(); i++) {
            this->m_Ghosts[i]->draw();
        }

    }

    void Juego::update(float deltaTime)
    {
        for(Ghost* g: m_Ghosts)
        {
            g->update(deltaTime);
        }
        this->m_Pacman->update(deltaTime);
        for(Block b: this->m_Paredes)
        {
            if(b.collide(this->m_Pacman->getPos(), this->m_Pacman->getRadius())) {
                m_Pacman->paredCollision(b.getPos());
			}

            for(Ghost* g: m_Ghosts)
            {
                if(b.collide(g->getPos(), g->getRadius()))
                {
                    g->paredCollision(b.getPos());
                }
            }
        }

        //Check for coins collected
        for(int i = 0; i < this->m_Coins.size(); i++) {
            Coin* c = this->m_Coins[i];
            if(c->collide(this->m_Pacman->getPos(), this->m_Pacman->getRadius()/10)) {
                if(c->isActive()) {
                    coinsCollectedPerBoard++;
                    std::cout <<"COINS PER BOARD: "<<coinsCollectedPerBoard <<"\n";
                    if (coinsCollectedPerBoard == m_Coins.size()) {
                        //Collected all the coins in the board
                        this->resetJuego();
                    }
                    //std::cout << "Collision with coin detected" << std::endl;
                    c->setActive(false);
                    this->increaseCoins(1);
                    //std::cout << "Coin count: " << this->getCoinCount() << std::endl;
                }
                break;
            }
        }

        if(this->ghost_powerup_time > 0 && clock() - this->ghost_powerup_time > 10000000) {
            this->ghost_powerup_time = 0;
            for(Ghost* g : this->m_Ghosts) {
                        g->setActive(true);
            }
        }

        //Check for PowerUps collected
        for(int i = 0; i < m_PowerUps.size(); i++) {
            PowerUp* powerup = m_PowerUps[i];
            if(powerup->collide(m_Pacman->getPos(), powerup->getRadius())){
                if(powerup->isActive()) {
                    std::cout << "Power Up!!" << std::endl;
                    this->ghost_powerup_time = clock();
                    
                    powerup->setActive(false);
                    for(Ghost* g : this->m_Ghosts) {
                        g->setActive(false);
                    }
                }
            }
        }

        //Check for ghost collision
        for(int i = 0; i < m_Ghosts.size(); i++) {
            Ghost* ghost = m_Ghosts[i];
            if(ghost->collide(m_Pacman->getPos(), 0.3)) {
                if(ghost->isActive()) {
                    this->resetJuego();
                }
                else {
                    this->increaseCoins(20);
                    ghost->setPos(ghost->getIniciatPos());
                    ghost->setActive(true);
                }
            }
        }

        m_LastBlockPos = m_BlockPos;
        m_BlockPos = m_Pacman->getBlockPos();
        //Si llego al centro de un bloque o esta quieto:
        if(m_LastBlockPos.x != m_BlockPos.x || m_LastBlockPos.y != m_BlockPos.y || (m_Pacman->getDirection().x == 0 && m_Pacman->getDirection().y == 0))
        {
            Vec2 direction = calcPacmanDir();
            m_Pacman->setDirection(direction);
            //std::cout <<"Block pos: " << m_BlockPos.x << ", " << m_BlockPos.y <<" .. Type of block: " << m_Map[(int)m_BlockPos.x][(int)m_BlockPos.y] << "\n";
        }
    }

    void Juego::resetJuego() {
        coinsCollectedPerBoard = 0;
        this->m_Paredes.clear();
        this->m_Coins.clear();
        this->m_PowerUps.clear();
        this->m_Ghosts.clear();
        this->buildBlocks();
        this->buildCoins();
        this->buildGhosts();
        this->buildPowerUps();
        this->m_Pacman = new Pacman();
        Vec3 pos = {playerSpawn.x, m_Pacman->getPos().y, playerSpawn.y};
        m_Pacman->setPos(pos);
    }

    void Juego::arrowsInput(int dir)
    {
        switch (dir)
        { 
            case 0:
                m_TurnTo = {0,1}; 
                break;
            case 1:
                m_TurnTo = {0,-1};
                break;
            case 2:
                m_TurnTo = {-1,0};
                break;
            case 3:
                m_TurnTo = {1,0};
                break;
        }
    }

    Pacman* Juego::getPacman()
    {
        return this->m_Pacman;
    }

    Vec2 Juego::calcPacmanDir()
    {
        //Entra solo cuando llega al centro de un bloque... toca probar si puede voltera en la dirección deseada
        Vec2 dirDeseada = {m_BlockPos.x + m_TurnTo.x, m_BlockPos.y + m_TurnTo.y};
        //std::cout << "dir deseada: " <<dirDeseada.x << " " << dirDeseada.y <<"\n";
        //std::cout << "dir: " <<m_Pacman->getDirection().x << " " << m_Pacman->getDirection().y <<"\n";
        if(m_Map[(int)dirDeseada.x][(int)dirDeseada.y] == 1)
        {
            //Si no puede voltear, probar si puede continuar adelante
            Vec2 dirActual = m_Pacman->getDirection();
            if(m_Map[(int)(m_BlockPos.x+dirActual.x)][(int)(m_BlockPos.y+dirActual.y)] == 1)
            {
                return {0,0}; //no se puede mover mas
            }
            else{
                //Puede seguir derecho
                return dirActual;
            }
        }
        else //Si puede voltear
        {
            return m_TurnTo;
        }

    }

