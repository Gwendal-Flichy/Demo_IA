#pragma once
#pragma once

#include "Tree.h"
#include "Boss.h"




namespace BT
{


    class Walk : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Walk(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(500);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class Sprint : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Sprint(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(1000);
            getGameObject()->SpeedLimit = 200.f;
            return Success;
        }


    };
    class Idle : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Idle(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            getGameObject()->setSpeed(0);
            getGameObject()->SpeedLimit = 100.f;
            return Success;
        }


    };

    class IsPlayerDead : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        IsPlayerDead(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
            {
                return Success;
            }
            return Failed;

        }
    };

    class FireShotgun : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        FireShotgun(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;


            if (m_delay == 0)
            {
            	getGameObject()->fireWithShotgun();
                m_delay = 10;
                return Success;
            }
            m_delay--;
            return Running;


        }
    private:
        int m_delay = 10;
    };

    class FireShotgunAfterKick : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        FireShotgunAfterKick(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;

            
			if (m_delay==10)
        		getGameObject()->fireWithShotgun();

            if (m_delay==0)
            {
                m_delay = 20;
                return Success;
            }
			m_delay--;
            return Running;


        }
    private:
        int m_delay= 20;
    };

    class FirePistol : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        FirePistol(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;

            if (m_delay == 0)
            {
                getGameObject()->fireWithPistol();
                m_delay = 10;
                return Success;
            }
            m_delay--;
            return Running;


        }
    private:
        int m_delay = 10;
    };

    class DoKick : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        DoKick(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;

            float Distance = getGameObject()->getDistanceToPlayer().getLength();
            if (Distance<=90)
            {
                if (m_delay== 25)
            		getGameObject()->Kick();

                if (m_delay == 0)
                {
                    m_delay = 25;
                    return Success;
                }
                m_delay--;
            }
            if (m_delay_ == 0)
            {
                m_delay_ = 70;
                return Success;
            }

            m_delay_--;
            return Running;


        }
    private:
        int m_delay = 25;
        int m_delay_ = 70;
    };

    class DoubleMelee : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        DoubleMelee(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;

            if (m_delay == 5)
                getGameObject()->RightMelee();
            if (m_delay == 35)
            {
                getGameObject()->LeftMelee();
            }

            if (m_delay == 0)
            {
                m_delay = 50;
                return Success;
            }
            m_delay--;

            return Running;


        }
    private:
        int m_delay = 50;
    };


    class FireLaser : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        FireLaser(ICompositeNode* parent)
    	: BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;

            if (m_delay==75)
            {
                getGameObject()->Laser();
            }
            if (m_delay == 0)
            {
                m_delay = 150;
	            return Success;
            	
            }
            m_delay--;
            return Running;

        }
    private:
        int m_delay = 150;
    };

    class Dash : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Dash(ICompositeNode* parent,const int& delay, const int& Cooldown, const float& angle=0)
    	: BehaviorNodeDecorator<Boss, IActionNode>(parent)
        , m_angle(angle)
        , m_delay(delay)
        ,m_Cooldown(Cooldown)
        {
        }

        Status tick() override
        {
            if (!getGameObject()->isCurrentTargetValid())
                return Failed;
            if (m_tempCooldown ==0)
        		getGameObject()->Dash(m_angle);
            if (m_tempCooldown == 0)
            {
                m_tempCooldown = m_Cooldown;
            }
            if (count == 0)
            {
	            getGameObject()->m_dashing = false;
                count = m_delay;
                return Success;
                
            }
            
        	
            count--;
            m_tempCooldown--;
            return Running;


        }
    private:
        float m_angle;
        int m_delay;
        int count=m_delay;
        int m_Cooldown;
        int m_tempCooldown = m_Cooldown;
        
    };

    class FindEnemy : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        FindEnemy(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {
            
            if (!getGameObject()->findValidTarget())
            {
                
                return Failed;
            }

            
            return Success;
        }
    };
	class PlayerDictance : public BehaviorNodeDecorator<Boss, IConditionalNode>
    {
    public:
        PlayerDictance(ICompositeNode* node,float min, float max)
            : BehaviorNodeDecorator<Boss, IConditionalNode>(node)
			,m_min(min)
			,m_max(max)

        {
        }

        bool condition()
        {
            float Distance = getGameObject()->getDistanceToPlayer().getLength();

            return Distance> m_min &&Distance< m_max;
        }
	private:
        float m_min;
        float m_max;
        
    };
    class SecondPhase : public BehaviorNodeDecorator<Boss, IConditionalNode>
    {
    public:
        SecondPhase(ICompositeNode* node)
            : BehaviorNodeDecorator<Boss, IConditionalNode>(node)
        {
        }

        bool condition()
        {

            return getGameObject()->getHP() <= getGameObject()->getMaxHP() / 2;
        }


    };

    class IsInCenter : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        IsInCenter(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {

            if (getGameObject()->getPosition().x <= getGameObject()->getCenter().x+1.5f && getGameObject()->getPosition().x >= getGameObject()->getCenter().x - 1.5f && getGameObject()->getPosition().y <= getGameObject()->getCenter().y + 1.5f && getGameObject()->getPosition().y >= getGameObject()->getCenter().y - 1.5f)
            {
                getGameObject()->GoingToCenter = false;
                return Success;
            }
            
            return Failed;
        }
    };

    class GotoCenter : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        GotoCenter(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent)
        {
        }

        Status tick() override
        {

            getGameObject()->GoingToCenter = true;
            return Success;
        }
    };

}
