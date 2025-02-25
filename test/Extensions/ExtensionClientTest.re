/*

 TODO: Bring back for exthost work

 open Oni_Core;
 open Oni_Core_Test;
 open Oni_Extensions;

 open TestFramework;

 open ExtensionClientHelper;
 open ExtHostProtocol;

 describe("ExtHostClient", ({describe, _}) => {
   describe("activation", ({test, _}) => {
     test("activates by language", ({expect}) => {
       let activations: ref(list(string)) = ref([]);
       let onDidActivateExtension = id => activations := [id, ...activations^];

       let isExpectedExtensionActivated = () =>
         isStringValueInList(activations, "oni-activation-events-test");

       withExtensionClient(
         ~onDidActivateExtension,
         client => {
           ExtHostClient.activateByEvent("onLanguage:testlang", client);

           Waiters.wait(isExpectedExtensionActivated, client);
           expect.bool(isExpectedExtensionActivated()).toBe(true);
         },
       );
     });

     test("activates by command", ({expect}) => {
       let activations: ref(list(string)) = ref([]);
       let onDidActivateExtension = id => activations := [id, ...activations^];

       let isExpectedExtensionActivated = () =>
         isStringValueInList(activations, "oni-activation-events-test");
       withExtensionClient(
         ~onDidActivateExtension,
         client => {
           ExtHostClient.activateByEvent(
             "onCommand:extension.activationTest",
             client,
           );

           Waiters.wait(isExpectedExtensionActivated, client);
           expect.bool(isExpectedExtensionActivated()).toBe(true);
         },
       );
     });
   });

   describe("commands", ({test, _}) =>
     test("executes simple command", ({expect}) => {
       let registeredCommands = empty();
       let messages = empty();

       let onShowMessage = append(messages);
       let onRegisterCommand = append(registeredCommands);

       let isExpectedCommandRegistered = () =>
         isStringValueInList(registeredCommands, "extension.helloWorld");

       let anyMessages = any(messages);

       withExtensionClient(
         ~onShowMessage,
         ~onRegisterCommand,
         client => {
           Waiters.wait(isExpectedCommandRegistered, client);
           expect.bool(isExpectedCommandRegistered()).toBe(true);

           clear(messages);

           ExtHostClient.executeContributedCommand(
             "extension.helloWorld",
             client,
           );

           Waiters.wait(anyMessages, client);
           expect.bool(anyMessages()).toBe(true);
         },
       );
     })
   );

   describe("DocumentsAndEditors", ({test, _}) => {
     let createInitialDocumentModel = (~lines, ~path, ()) => {
       ModelAddedDelta.create(
         ~uri=Uri.fromPath(path),
         ~lines,
         ~modeId="test_language",
         ~isDirty=false,
         (),
       );
     };
     test("document added successfully", ({expect}) => {
       let registeredCommands = empty();
       let messages = emptyInfoMsgs();

       let onShowMessage = appendInfoMsg(messages);
       let onRegisterCommand = append(registeredCommands);

       let isExpectedCommandRegistered = () =>
         isStringValueInList(registeredCommands, "extension.helloWorld");

       let didGetOpenMessage = () =>
         doesInfoMessageMatch(messages, info =>
           String.equal(info.filename, "test.txt")
           && String.equal(info.messageType, "workspace.onDidOpenTextDocument")
         );

       withExtensionClient(
         ~onRegisterCommand,
         ~onShowMessage,
         client => {
           Waiters.wait(isExpectedCommandRegistered, client);
           expect.bool(isExpectedCommandRegistered()).toBe(true);

           ExtHostClient.addDocument(
             createInitialDocumentModel(
               ~lines=["Hello world"],
               ~path="test.txt",
               (),
             ),
             client,
           );
           Waiters.wait(didGetOpenMessage, client);
           expect.bool(didGetOpenMessage()).toBe(true);
         },
       );
     });

     test("document updated successfully", ({expect}) => {
       let registeredCommands = empty();
       let messages = emptyInfoMsgs();

       let onShowMessage = appendInfoMsg(messages);
       let onRegisterCommand = append(registeredCommands);

       let isExpectedCommandRegistered = () =>
         isStringValueInList(registeredCommands, "extension.helloWorld");

       let didGetOpenMessage = () =>
         doesInfoMessageMatch(messages, info =>
           String.equal(info.filename, "test.txt")
           && String.equal(info.messageType, "workspace.onDidOpenTextDocument")
         );

       let didGetUpdateMessage = () =>
         doesInfoMessageMatch(messages, info =>
           String.equal(info.filename, "test.txt")
           && String.equal(
                info.messageType,
                "workspace.onDidChangeTextDocument",
              )
           && String.equal(
                info.fullText,
                "Greetings" ++ Eol.toString(Eol.default) ++ "world",
              )
         );

       withExtensionClient(
         ~onShowMessage,
         ~onRegisterCommand,
         client => {
           Waiters.wait(isExpectedCommandRegistered, client);
           expect.bool(isExpectedCommandRegistered()).toBe(true);

           ExtHostClient.addDocument(
             createInitialDocumentModel(
               ~lines=["hello", "world"],
               ~path="test.txt",
               (),
             ),
             client,
           );
           Waiters.wait(didGetOpenMessage, client);
           expect.bool(didGetOpenMessage()).toBe(true);

           let contentChange =
             ModelContentChange.create(
               ~range=
                 Range.create(
                   ~startLine=ZeroBasedIndex(0),
                   ~endLine=ZeroBasedIndex(0),
                   ~startCharacter=ZeroBasedIndex(0),
                   ~endCharacter=ZeroBasedIndex(5),
                   (),
                 ),
               ~text="Greetings",
               (),
             );

           let modelChangedEvent =
             ModelChangedEvent.create(
               ~changes=[contentChange],
               ~eol=Eol.default,
               ~versionId=1,
               (),
             );
           ExtHostClient.updateDocument(
             Uri.fromPath("test.txt"),
             modelChangedEvent,
             true,
             client,
           );

           Waiters.wait(didGetUpdateMessage, client);
           expect.bool(didGetUpdateMessage()).toBe(true);
         },
       );
     });
   });
 });
 */
