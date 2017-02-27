trait Command {
    fn execute(&self);
    fn undo(&self);
    fn redo(&self) { self.execute(); }
}

////////////////////////////////////////

struct Bulb;

impl Bulb {
    fn turn_on(&self) {
        println!("I'm on");
    }

    fn turn_off(&self) {
        println!("I'm off");
    }
}

////////////////////////////////////////

struct TurnOn<T> {
    data: T,
}

struct TurnOff<T> {
    data: T,
}

impl<'a> Command for TurnOn<&'a Bulb> {
    fn execute(&self) {
        self.data.turn_on();
    }

    fn undo(&self) {
        self.data.turn_off();
    }
}

impl<'a> Command for TurnOff<&'a Bulb> {
    fn execute(&self) {
        self.data.turn_off();
    }

    fn undo(&self) {
        self.data.turn_on();
    }
}

////////////////////////////////////////

#[derive(Default)]
struct RemoteControl;

impl RemoteControl {
    fn submit<T: Command>(&self, command: T) {
        command.execute();
    }
}

fn main() {
    let bulb = Bulb {};
    let turn_on = TurnOn { data: &bulb };
    let turn_off = TurnOff { data: &bulb };

    let remote = RemoteControl {};
    remote.submit(turn_on);
    remote.submit(turn_off);
}
