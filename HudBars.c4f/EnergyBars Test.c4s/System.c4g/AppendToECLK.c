/*-- Hud Bars Example --*/

#appendto ECLK 
#strict 3

local acid_resist;

protected func Initialize(a,b,c)
{
  DoMagicEnergy(50,nil,true);
  acid_resist = 1000000;
  UpdateBars();
  return _inherited(a,b,c);
}

protected func UpdateBars() {
  // normally you would have only some of these, 
  // here we have many energy bars to demonstrate
  // many possibilities at once
  DefineHudBars({
    D = {file = "EnergyBars", amount = 3}, // Default graphics
    S = {file = "SEnergyBars", amount = 6, scale = 200} // highres example graphics
  },[
    {name = "DefaultEnergy", gfx = "D", index = 0, physical = EBP_Energy}, // energy with default graphics
    {name = "DefaultMagic",  gfx = "D", index = 1, physical = EBP_Magic},  // magic with default graphics
    {name = "DefaultBreath", gfx = "D", index = 2, physical = EBP_Breath}, // breath with default graphics
    
    {name = "Energy", gfx = "S", index = 0, physical = EBP_Energy}, // energy with custom graphics
    {name = "Magic",  gfx = "S", index = 1, physical = EBP_Magic},  // redundant with slime but enabled for demonstration purpouses
    {name = "Slime",  gfx = "S", index = 3, physical = EBP_Magic,  hide = EBH_Empty}, // reskin of magic, also could be completely independent if wanted
    {name = "Acid",   gfx = "S", index = 4, hide = EBH_Empty},
    {name = "Breath", gfx = "S", index = 2, physical = EBP_Breath},
    
    // overlay example
    // graphics don't look that great, 
    // but maybe somebody manages to create a cool looking combined hud bar
    [
      {name = "OverlayEnergy", gfx = "S", index = 0, physical = EBP_Energy},
      {name = "AcidOverlay", gfx = "S", index = 5, visible = false, hide = EBH_Empty}
    ]
  ]);
  SetHudBarVisibility("AcidOverlay", true); // visible is defined as false, just for demonstration
}

protected func UpdateBarValues() {
  SetHudBarValue("Acid", acid_resist);
  SetHudBarValue("AcidOverlay", acid_resist);
}
