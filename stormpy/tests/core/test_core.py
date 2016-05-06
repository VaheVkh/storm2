import stormpy

class TestCore:
    def test_init(self):
        stormpy.set_up("")
    
    def test_build_parametric_model_from_prism_program(self):
        program = stormpy.parse_program("../examples/pdtmc/brp/brp_16_2.pm")
        assert program.nr_modules() == 5
        assert program.model_type() == stormpy.PrismModelType.DTMC
        assert program.has_undefined_constants()
        prop = "P=? [F \"target\"]"
        formulas = stormpy.parse_formulas_for_program(prop, program)
        pair = stormpy.build_parametric_model_from_prism_program(program, formulas)
        model = pair.model
        assert model.nr_states() == 613
        assert model.nr_transitions() == 803
        assert model.model_type() == stormpy.ModelType.DTMC
        assert model.parametric()
    
    def test_bisimulation(self):
        program = stormpy.parse_program("../examples/dtmc/crowds/crowds5_5.pm")
        assert program.nr_modules() == 1
        assert program.model_type() == stormpy.PrismModelType.DTMC
        prop = "P=? [F \"observe0Greater1\"]"
        formulas = stormpy.parse_formulas_for_program(prop, program)
        pair = stormpy.build_model_from_prism_program(program, formulas)
        model = pair.model
        assert model.nr_states() == 7403
        assert model.nr_transitions() == 13041
        assert model.model_type() == stormpy.ModelType.DTMC
        assert not model.parametric()
        model_bisim = stormpy.perform_bisimulation(model, formulas[0], stormpy.BisimulationType.STRONG)
        assert model_bisim.nr_states() == 64
        assert model_bisim.nr_transitions() == 104
        assert model_bisim.model_type() == stormpy.ModelType.DTMC
        assert not model_bisim.parametric()
    
    def test_parametric_bisimulation(self):
        program = stormpy.parse_program("../examples/pdtmc/crowds/crowds_3-5.pm")
        assert program.nr_modules() == 1
        assert program.model_type() == stormpy.PrismModelType.DTMC
        assert program.has_undefined_constants()
        prop = "P=? [F \"observe0Greater1\"]"
        formulas = stormpy.parse_formulas_for_program(prop, program)
        pair = stormpy.build_parametric_model_from_prism_program(program, formulas)
        model = pair.model
        assert model.nr_states() == 1367
        assert model.nr_transitions() == 2027
        assert model.model_type() == stormpy.ModelType.DTMC
        assert model.parametric()
        model_bisim = stormpy.perform_parametric_bisimulation(model, formulas[0], stormpy.BisimulationType.STRONG)
        assert model_bisim.nr_states() == 80
        assert model_bisim.nr_transitions() == 120
        assert model_bisim.model_type() == stormpy.ModelType.DTMC
        assert model_bisim.parametric()
    
    def test_state_elimination(self):
        import pycarl
        program = stormpy.parse_program("../examples/pdtmc/brp/brp_16_2.pm")
        prop = "P=? [F \"target\"]"
        formulas = stormpy.parse_formulas_for_program(prop, program)
        pair = stormpy.build_parametric_model_from_prism_program(program, formulas)
        model = pair.model
        assert model.nr_states() == 613
        assert model.nr_transitions() == 803
        assert model.model_type() == stormpy.ModelType.DTMC
        assert model.parametric()
        result = stormpy.perform_state_elimination(model, formulas[0])
