package org.csu.corbasim;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.GnuParser;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.csu.cpp.output.CppBeautifier;
import org.csu.idl.idlmm.TranslationUnit;
import org.csu.idl.preprocessor.Preprocessor;
import org.csu.idl.xtext.loader.IDLLoader;
import org.eclipse.internal.xpand2.pr.ProtectedRegionResolverImpl;
import org.eclipse.xpand2.XpandExecutionContextImpl;
import org.eclipse.xpand2.XpandFacade;
import org.eclipse.xpand2.output.Outlet;
import org.eclipse.xpand2.output.OutputImpl;
import org.eclipse.xtend.expression.Variable;
import org.eclipse.xtext.conversion.impl.AbstractDeclarativeValueConverterService;

public class Generator {

	private Map<String, Variable> globalVarsMap = new HashMap<String, Variable>();

	private IDLLoader loader = new IDLLoader();

	private Preprocessor preprocessor = null;

	public Generator() {
		preprocessor = loader.getPreprocessor();

		// Default values
		globalVarsMap.put("StubHppSuffix", new Variable("StubHppSuffix", stubHppSuffix));
		globalVarsMap.put("StubCppSuffix", new Variable("StubCppSuffix", stubCppSuffix));
		globalVarsMap.put("SkelHppSuffix", new Variable("SkelHppSuffix", skelHppSuffix));
		globalVarsMap.put("SkelCppSuffix", new Variable("SkelCppSuffix", skelCppSuffix));
		globalVarsMap.put("SkelImplHppSuffix", new Variable("SkelImplHppSuffix", skelImplHppSuffix));
		globalVarsMap.put("SkelImplCppSuffix", new Variable("SkelImplCppSuffix", skelImplCppSuffix));
	}

	public void run(String[] args) {

		proccessArgs(args);
		
		try {
			loader.load(filePath);
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
		TranslationUnit model = loader.getModel();
		
		// Xpand
		generate(model);
	}

	private void generate(TranslationUnit model) {
		// http://www.peterfriese.de/using-xpand-in-your-eclipse-wizards/

		// Configure outlets
		OutputImpl output = new OutputImpl();
		Outlet outlet = new Outlet("model");
		outlet.setOverwrite(true);
		outlet.addPostprocessor(new CppBeautifier());
		outlet.setPath(targetDir);
		output.addOutlet(outlet);

		// Protected regions
		ProtectedRegionResolverImpl pr = new ProtectedRegionResolverImpl();
		pr.setSrcPathes(prSrcPaths);
		pr.setDefaultExcludes(true);
		pr.setIgnoreList("*.swp");

		// Execution context
		XpandExecutionContextImpl execCtx = new XpandExecutionContextImpl(output, pr, globalVarsMap, null, null);
		execCtx.registerMetaModel(new org.eclipse.xtend.type.impl.java.JavaBeansMetaModel());

		// Generate
		XpandFacade facade = XpandFacade.create(execCtx);
		String templatePath = "templates::corbasim::Main::main";
		facade.evaluate(templatePath, model);
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Generator().run(args);
	}

	//
	// Command line options
	// http://snippets.dzone.com/posts/show/3504
	//

	@SuppressWarnings("unchecked")
	private void proccessArgs(String[] args) {
		CommandLineParser parser = new GnuParser();
		try {
			cmd = parser.parse(options, args);
		} catch (ParseException e) {
			System.err.println("Error parsing arguments");
			System.exit(1);
		}

		if (cmd.hasOption("h")) {
			System.out.println("Options:");
			for (Option opt_ : (Collection<Option>) options.getOptions()) {
				System.out.println("-" + opt_.getOpt() + "\t" + opt_.getDescription());
			}
			System.exit(0);
		}

		for (Option opt : cmd.getOptions()) {
			if (opt.getOpt() == ("o"))
				targetDir = opt.getValue();

			if (opt.getOpt() == ("hc"))
				globalVarsMap.get("StubHppSuffix").setValue(opt.getValue());

			if (opt.getOpt() == ("hs"))
				globalVarsMap.get("SkelHppSuffix").setValue(opt.getValue());

			if (opt.getOpt() == ("hT"))
				globalVarsMap.get("SkelImplHppSuffix").setValue(opt.getValue());

			if (opt.getOpt() == ("sc"))
				globalVarsMap.get("StubCppSuffix").setValue(opt.getValue());

			if (opt.getOpt() == ("ss"))
				globalVarsMap.get("SkelCppSuffix").setValue(opt.getValue());

			if (opt.getOpt() == ("sT"))
				globalVarsMap.get("SkelImplCppSuffix").setValue(opt.getValue());

			if (opt.getOpt() == ("p"))
				prSrcPaths += opt.getValue() + ",";

			// Preproccessor options

			if (opt.getOpt() == ("D"))
				preprocessor.addMacroDefinition(opt.getValue());

			if (opt.getOpt() == ("U"))
				preprocessor.undefMacro(opt.getValue());

			if (opt.getOpt() == ("I"))
				preprocessor.addIncludePath(opt.getValue());

		}

		globalVarsMap.put("targetDir", new Variable("targetDir", targetDir));

		if (!cmd.hasOption("p"))
			prSrcPaths = targetDir;

		// Verbose
		if (!cmd.hasOption("v")) {
			// Solo errores
			System.setProperty("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.NoOpLog");
			Logger.getRootLogger().setLevel(Level.ERROR);
			Logger.getLogger(AbstractDeclarativeValueConverterService.class).setLevel(Level.ERROR);
		}

		// IDL file
		if (cmd.getArgList().size() == 1)
			filePath = (String) cmd.getArgList().get(0);
		else {
			System.err.println("No IDL file specified or more than one.");
			System.exit(1);
		}
		
		// Generator options
		genClient = cmd.hasOption("Gclient");
		genInjector = cmd.hasOption("Ginjector");
		genServer = cmd.hasOption("Gserver");
		genPyStim = cmd.hasOption("Gpystim");
		genInterpreter = cmd.hasOption("Ginterpreter");
		
		genCMake = !cmd.hasOption("Ncmake");
		
		globalVarsMap.put("genClient", new Variable("genClient", genClient));
		globalVarsMap.put("genInjector", new Variable("genInjector", genInjector));
		globalVarsMap.put("genServer", new Variable("genServer", genServer));
		globalVarsMap.put("genPyStim", new Variable("genPyStim", genPyStim));
		globalVarsMap.put("genInterpreter", new Variable("genInterpreter", genInterpreter));
		globalVarsMap.put("genCMake", new Variable("genCMake", genCMake));
	}

	private static Options options = null; // Command line options

	private CommandLine cmd = null; // Command Line arguments

	// By default
	private String targetDir = ".";
	private String prSrcPaths = "";
	private String filePath = null;
	
	// Generartor options
	private boolean genClient = false;
	private boolean genServer = false;
	private boolean genInjector = false;
	private boolean genPyStim = false;
	private boolean genInterpreter = false;
	private boolean genCMake = true;

	// TAO defaults
	private static String stubHppSuffix = "C.h";
	private static String skelHppSuffix = "S.h";
	private static String skelImplHppSuffix = "I.h";
	private static String stubCppSuffix = "C.cpp";
	private static String skelCppSuffix = "S.cpp";
	private static String skelImplCppSuffix = "I.cpp";

	static {
		options = new Options();

		// options.addOption(opt, hasArg, description);
		// options.addOption(opt, longOpt, hasArg, description);

		options.addOption("v", false, "Verbose.");

		// ORB options
		options.addOption("o", true, "Output directory for the generated files. Default is current directory.");
		options.addOption("hc", true, "Client's header file name ending. Default is " + stubHppSuffix);
		options.addOption("hs", true, "Server's header file name ending. Default is " + skelHppSuffix);
		options.addOption("hT", true, "Server's template header file name ending. Default is " + skelImplHppSuffix);
		options.addOption("cs", true, "Client's header file name ending. Default is " + stubCppSuffix);
		options.addOption("ss", true, "Server's header file name ending. Default is " + skelCppSuffix);
		options.addOption("sT", true, "Server's template header file name ending. Default is " + skelImplCppSuffix);

		options.addOption("E", false, "Only invoke the preprocessor.");
		options.addOption("h", false, "Show this help text.");

		options.addOption("Gclient", false, "Generate GUI client.");
		options.addOption("Ginjector", false, "Generate script injector.");
		options.addOption("Gserver", false, "Generate dummy server.");
		options.addOption("Gpystim", false, "Generate a PyStim.");
		options.addOption("Ginterpreter", false, "Generate a script interpreter.");
		
		options.addOption("Ncmake", false, "Do not generate CMake files.");

		options.addOption("p", true, "Protected regions source paths. Default is output directory.");

		// Preproccessor options
		options.addOption("D", true, "Passed to the preprocessor.");
		options.addOption("U", true, "Passed to the preprocessor.");
		options.addOption("I", true, "Passed to the preprocessor.");

	}
}
