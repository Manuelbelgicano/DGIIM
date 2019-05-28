#encoding:utf-8

require "./lib/LootToUI.rb"

module Deepspace
  # Botín
  class Loot
    attr_reader :nSupplies, :nWeapons, :nShields, :nHangars, :nMedals, :getEfficient, :spaceCity

    def initialize(supplies_num,weapons_num,shields_num,hangars_num,medals_num,ef=false,city=false)
      @nSupplies = supplies_num
      @nWeapons = weapons_num
      @nShields = shields_num
      @nHangars = hangars_num
      @nMedals = medals_num
      @getEfficient = ef
      @spaceCity = city
    end

    def efficient
      @getEfficient
    end

    def getUIversion
      LootToUI.new(self)
    end

    def to_s
      getUIversion.to_s
    end
  end
end
