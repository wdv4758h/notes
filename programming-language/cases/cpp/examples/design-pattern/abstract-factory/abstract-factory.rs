// Rust

////////////////////////////////////////

trait Door {
    fn description(&self);
}

trait DoorFittingExpert {
    fn description(&self);
}

trait DoorAbstractFactory<D: Door + Default, E: DoorFittingExpert + Default> {
    fn new_door(&self) -> D { Default::default() }
    fn new_expert(&self) -> E { Default::default() }
}

////////////////////////////////////////

#[derive(Default)]
struct WoodenDoor;

#[derive(Default)]
struct IronDoor;

impl Door for WoodenDoor {
    fn description(&self) { println!("A wooden door!"); }
}

impl Door for IronDoor {
    fn description(&self) { println!("A iron door!"); }
}

////////////////////////////////////////

#[derive(Default)]
struct Carpenter;

#[derive(Default)]
struct Welder;

impl DoorFittingExpert for Carpenter {
    fn description(&self) { println!("I can only fit wooden door!"); }
}

impl DoorFittingExpert for Welder {
    fn description(&self) { println!("I can only fit iron door!"); }
}

////////////////////////////////////////

struct WoodenDoorFactory;
struct IronDoorFactory;

impl DoorAbstractFactory<WoodenDoor, Carpenter> for WoodenDoorFactory {}
impl DoorAbstractFactory<IronDoor, Welder> for IronDoorFactory {}

fn main() {
    {
        let factory = WoodenDoorFactory{};
        let door = factory.new_door();
        let expert = factory.new_expert();
        door.description();
        expert.description();
    }
    {
        let factory = IronDoorFactory{};
        let door = factory.new_door();
        let expert = factory.new_expert();
        door.description();
        expert.description();
    }
}
