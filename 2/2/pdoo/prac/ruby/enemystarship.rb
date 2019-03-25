#encoding:utf-8

require_relative "./lib/EnemyToUI.rb"
require_relative "./shotresult.rb"

module Deepspace
  # Nave enemiga
  class EnemyStarship

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
      EnemyStarship.new(e.name,e.ammoPower,e.shieldPower,e.loot,e.damage)
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

    def getUIVersion
      EnemyToUI.new(self)
    end

    def to_s
      "name = #{@name}\n
      ammoPower = #{@ammoPower}\n
      shieldPower = #{@shieldPower}\n
      loot = #{@loot.to_s}\n
      damage = #{@damage.to_s}"
    end
  end
end
