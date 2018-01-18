open Opium.Std

let root request =
  `String ("Oi get out") |> respond'

let _ = App.empty
        |> get "/" root
        |> App.run_command
