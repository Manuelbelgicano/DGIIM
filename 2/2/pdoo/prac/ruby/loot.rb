#encoding:utf-8

require "./lib/LootToUI.rb"

module Deepspace
  # Botín
  class Loot
    attr_reader :nSupplies, :nWeapons, :nShields, :nHangars, :nMedals

    def initialize(supplies_num,weapons_num,shields_num,hangars_num,medals_num)
      @nSupplies = supplies_num
      @nWeapons = weapons_num
      @nShields = shields_num
      @nHangars = hangars_num
      @nMedals = medals_num
    end

    def getUIversion
      LootToUI.new(self)
    end

    def to_s
      getUIversion.to_s
    end
  end
end
