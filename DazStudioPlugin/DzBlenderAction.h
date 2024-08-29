#pragma once
#include <dzaction.h>
#include <dznode.h>
#include <dzjsonwriter.h>
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include <dzexporter.h>

#include <DzBridgeAction.h>
#include "DzBlenderDialog.h"

class UnitTest_DzBlenderAction;

#include "dzbridge.h"

class QProcess;
class DzBlenderUtils
{
public:
	static int ExecuteBlenderScripts(QString sBlenderExecutablePath, QString sCommandlineArguments, QString sWorkingPath, QProcess* thisProcess);
	static bool GenerateBlenderBatchFile(QString batchFilePath, QString sBlenderExecutablePath, QString sCommandArgs);
	static bool PrepareAndRunBlenderProcessing(QString sDestinationFbx, QString sBlenderExecutablePath, QProcess* thisProcess, int nPythonExceptionExitCode);
};

class DzBlenderExporter : public DzExporter {
	Q_OBJECT
public:
	DzBlenderExporter() : DzExporter(QString("blend")) {};

public slots:
	virtual void getDefaultOptions(DzFileIOSettings* options) const {};
	virtual QString getDescription() const override { return QString("Blender File"); };
	virtual bool isFileExporter() const override { return true; };

protected:
	virtual DzError	write(const QString& filename, const DzFileIOSettings* options) override;
};

class DzBlenderAction : public DZ_BRIDGE_NAMESPACE::DzBridgeAction {
	 Q_OBJECT
public:
	DzBlenderAction();

protected:
	 void executeAction() override;
	 Q_INVOKABLE void writeConfiguration() override;
	 Q_INVOKABLE void setExportOptions(DzFileIOSettings& ExportOptions) override;
	 virtual QString readGuiRootFolder() override;
	 Q_INVOKABLE virtual bool readGui(DZ_BRIDGE_NAMESPACE::DzBridgeDialog*) override;

	 Q_INVOKABLE QString createBlenderFiles(bool replace = true);

	 Q_INVOKABLE bool createUI();
	 Q_INVOKABLE bool executeBlenderScripts(QString sFilePath, QString sCommandlineArguments);

	 virtual bool preProcessScene(DzNode* parentNode) override;
	 virtual bool postProcessFbx(QString fbxFilePath) override;

	 int m_nPythonExceptionExitCode = 11;  // arbitrary exit code to check for blener python exceptions
	 int m_nBlenderExitCode = 0;
	 QString m_sBlenderExecutablePath = "";

	 bool m_bUseBlenderTools = false;
	 QString m_sOutputBlendFilepath = "";
	 QString m_sTextureAtlasMode = "";
	 QString m_sExportRigMode = "";

	 int m_nTextureAtlasSize = 0;
	 bool m_bEnableGpuBaking = false;
	 bool m_bEmbedTexturesInOutputFile = false;


	 friend class DzBlenderExporter;
#ifdef UNITTEST_DZBRIDGE
	friend class UnitTest_DzBlenderAction;
#endif

};
