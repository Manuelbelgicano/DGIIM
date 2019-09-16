/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import Deepspace.GameUniverse;
import View.View;
import java.util.ArrayList;
import Deepspace.CombatResult;
import Deepspace.GameState;
import Deepspace.GameUniverseToUI;

/**
 *
 * @author diagmatrix
 */
public class Controllerv2 {
    private View view;
    private static Controllerv2 instance = null;
    private GameUniverse model = new GameUniverse();
    
    public static Controllerv2 getInstance() {
        if (instance==null)
            instance = new Controllerv2();
        return instance;
    }
    
    private Controllerv2() {}
    
    public void setModelView(GameUniverse _model,View _view) {
        model = _model;
        view = _view;
        view.setController(this);
    }
    
    public void start() {
        ArrayList<String> names = view.getNames();
        model.init(names);
        view.updateView();
        view.showView();
    }
    
    public CombatResult combat() {
        CombatResult aux = model.combat();
        view.updateView();
        return aux;
    }
    
    public GameUniverseToUI getModelUIversion() { return model.getUIversion(); }
    
    public GameState getState() { return model.getState(); }
    
    public void discardWeapons(ArrayList<Integer> w) {
        for (int i=w.size()-1;i>-1;i--)
            model.discardWeapon(w.get(i));
        view.updateView();
    }
    
    public void discardWeaponsInHangar(ArrayList<Integer> w) {
        for (int i=w.size()-1;i>-1;i--)
            model.discardWeaponInHangar(w.get(i));
        view.updateView();
    }
    
    public void discardShields(ArrayList<Integer> s) {
        for (int i=s.size()-1;i>-1;i--)
            model.discardWeapon(s.get(i));
        view.updateView();
    }
    
    public void discardShieldsInHangar(ArrayList<Integer> s) {
        for (int i=s.size()-1;i>-1;i--)
            model.discardWeaponInHangar(s.get(i));
        view.updateView();
    }
    
    public void mountWeapons(ArrayList<Integer> w) {
        for (int i=w.size()-1;i>-1;i--)
            model.mountWeapon(w.get(i));
        view.updateView();
    }
    
    public void mountShields(ArrayList<Integer> s) {
        for (int i=s.size()-1;i>-1;i--)
            model.mountShieldBooster(s.get(i));
        view.updateView();
    }
    
    public void discardHangar() {
        model.discardHangar();
        view.updateView();
    }
    
    public void finish(int i) { 
        if (view.confirmExitMessage())
            System.exit(i); 
    }
    
    public boolean nextTurn() {
        boolean aux = model.nextTurn();
        view.updateView();
        return aux;
    }
    
    public boolean haveAWinner() {
        return model.haveAWinner();
    }
}
