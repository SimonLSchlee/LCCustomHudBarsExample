/*-- Aquaclonk --*/

#strict

#include CLNK

protected func CheckAcid() {
  if (GetMaterial() == Material("Acid") && acid_resist > 0) SetGraphics("Acid");
  else SetGraphics("");
}

protected func UpdateAcidResist() {
  if (GetMaterial() != Material("Acid"))
  {
    acid_resist+=5000;
    if (acid_resist > 1000000)
    {
      acid_resist = 1000000;
    }
  } 
  else 
  {
    acid_resist-=2000;
    if (acid_resist < 0)
    {
      if(!Random(10)) DoEnergy(-1);
      acid_resist = 0;
    }
  }
  
  UpdateBarValues();
  CheckAcid();
}


// Prä-CE-Aquaclonks hatten schlechtere Physicals
private func UpdatePhysical (string phys) 
  {
  if (GetPhysical (phys, 1) < GetPhysical (phys, 0, 0, GetID ())) SetPhysical (phys, GetPhysical (phys, 0, 0, GetID ()), 1);
  }

protected func Initialize(a,b,c)
  {
  inherited (a,b,c);
  UpdatePhysical ("Breath");
  UpdatePhysical ("Walk");
  UpdatePhysical ("Scale");
  UpdatePhysical ("Hangle");
  UpdatePhysical ("Dig");
  UpdatePhysical ("Push");
  UpdatePhysical ("Fight");
  DoMagicEnergy(1000);
  }

// Zur Sicherheit, damit Überladungen keinen Fehler beim Starten geben
protected func Scaling()
  {
  var szDesiredAction;
  if (GetYDir()>0) szDesiredAction = "ScaleDown"; else szDesiredAction = "Scale";
  if (GetAction() ne szDesiredAction) SetAction(szDesiredAction);
  return(1);   
  }

protected func CheckStuck()
{                   
  // Verhindert Festhängen am Mittelvertex
  if(!GetXDir()) if(Abs(GetYDir()) < 5)
    if(GBackSolid(0, 3))
      SetPosition(GetX(), GetY() + 1);
}

protected func ContactBottom() {
  var act = GetAction();
  if (act eq "Swim")
    SetAction("Walk");
  return(1);
}
  

/* Status */

public func IsAquaClonk() { return true; }
