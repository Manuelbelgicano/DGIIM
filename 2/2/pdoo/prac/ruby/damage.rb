#encoding:utf-8

require "./lib/DamageToUI.rb"
require_relative "./weapontype.rb"
require_relative "./weapon.rb" # No creo que sea necesario

module Deepspace
  # Daño
  class Damage

    attr_reader :nWeapons, :weapons, :nShields

    def initialize(w,wl,s)
      @nWeapons = w
      @weapons = wl
      @nShields = s
    end
    
    # Constructor de daño con número genérico de armas
    def self.newNumericWeapons(w,s)
      new(w,nil,s)
    end

    # Constructor de daño con tipo específico de armas
    def self.newSpecificWeapons(wl,s)
      new(-1,wl,s)
    end

    def getUIversion
      DamageToUI.new(self)
    end
    
    def to_s
      getUIversion.to_s
    end

    # Comprueba si el array 'w' contiene armas del tipo 't'
    private def arrayContainsType(w,t)
      w.each_index do |i|
        if w[i].type==t
          return i
        end
      end
      return -1
    end

    # Ajusta el objeto al equipo del jugador
    def adjust(w,s)
      newNShields = [s.length,@nShields].min
      if @nWeapons==-1
        newWeapons = Array.new(@weapons)
        newWeapons.each do |type|
          if arrayContainsType(w,type)==-1
            newWeapons.delete(type)
          end
        end
        return self.class.newSpecificWeapons(newWeapons,newNShields)
      elsif @weapons==nil
        newNWeapons = [w.length,@nWeapons].min
        return self.class.newNumericWeapons(newNWeapons,newNShields)
      end
    end

    # Elimina un arma del daño
    def discardWeapon(w)
      if @weapons!=nil
        index = arrayContainsType(@weapons,w.type)
        if index!=-1
          @weapons.delete_at(index)
        end
      elsif @nWeapons>0
        @nWeapons -= 1
      end
    end

    # Elimina un potenciador de escudo
    def discardShieldBooster
      if @nShields>0
        @nShields -= 1
      end
    end

    # Comprueba si el daño no tiene efecto
    def hasNoEffect
      if @nShields==0
        if @weapons!=nil and @weapons.length==0
          return true
        elsif @nWeapons==0
          return true
        else
          return false
        end
      end
      return false
    end

    private_class_method :new

  end
end
