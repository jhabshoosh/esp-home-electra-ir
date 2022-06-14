# esp-home-electra-ir
Electra IR ESP Home Component

Convenience Repo to make installing @liads 's custom component for electra ac (rc-3 ir remote)

Big thank you to @liad for creating this component.


Example Usage:
```
sensor:

climate:
  - platform: custom
    lambda: |-
      auto electra_climate = new ElectraClimate();
      electra_climate->set_sensor(id(my_temperature_sensor)); // Optional
      electra_climate->set_transmitter(id(my_ir_transmitter));
      App.register_component(electra_climate);
      return {electra_climate};

    climates:
      - name: "My Electra AC"
```