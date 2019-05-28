#encoding:utf-8

require "./lib/EnemyToUI.rb"
require_relative "./shotresult.rb"
require_relative "./damage.rb"
require_relative "./loot.rb"

module Deepspace
  # Nave enemiga
  class EnemyStarShip

    attr_reader :name, :ammoPower, :shieldPower, :loot, :damage

    def initialize(n,a,s,l,d)
      @name = n
      @ammoPower = a
      @shieldPower = s
      @loot = l
      @damage = d
    end

    # Constructor por copia
    def self.newCopy(e)
      EnemyStarShip.new(e.name,e.ammoPower,e.shieldPower,e.loot,e.damage)
    end

    # Análogo al consultor del atributo 'ammoPower'
    def fire
      @ammoPower
    end

    # Análogo al consultor del atributo 'shieldPower'
    def protection
      @shieldPower
    end
    
    # Determina si la nave aguanta un disparo
    def recieveShot(shot)
      if @shieldPower<shot
        return ShotResult::DONOTRESIST
      else
        return ShotResult::RESIST
      end
    end

    def getUIversion
      EnemyToUI.new(self)
    end

    def to_s
      getUIversion.to_s
    end
  end
end
