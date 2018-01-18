trait StateMachine {
    fn transition<T>(mut &self, T input);
    fn state(&self) -> int;
    fn act(mut &self);
}
