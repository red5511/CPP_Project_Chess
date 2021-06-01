import 'package:firebase_database/firebase_database.dart';
import 'package:firebase_database/ui/firebase_animated_list.dart';
import 'package:flutter/material.dart';

class AddExercisePage extends StatefulWidget {
  final trainingKey;

  AddExercisePage(this.trainingKey);

  @override
  _AddExercisePageState createState() => _AddExercisePageState();
}

class _AddExercisePageState extends State<AddExercisePage> {
  Query _ref;
  var _key = Key('anotherkey');
  List<String> chest = ['wyciskanie sztangi', 'test'];
  List<String> biceps = ['podnoszeni hantli', 'test2'];
  List<String> litems = ['test'];
  void initState() {
    super.initState();
    _ref = FirebaseDatabase.instance.reference().child('exercises');
  }

  getData(name) {
    Widget _buildContactItem({Map notes, var key}) {
      return Container(
          decoration: new BoxDecoration(
            border: Border.all(color: Colors.brown, width: 5),
            color: Colors.yellow,
          ),
          padding: EdgeInsets.only(top: 10, bottom: 10, left: 15, right: 10),
          margin: EdgeInsets.only(top: 20, left: 20, right: 20),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Icon(Icons.event_note),
                ],
              ),
              Text(
                notes['name'],
                style: TextStyle(fontSize: 22),
              ),
            ],
          ));
    }
  }

  /*
  var url1;
  Future getImage(name) async {
    final ref = FirebaseStorage.instance.ref().child(name);
    print(ref);
    var url = await ref.getDownloadURL();
    //print('url: ' + url);
    url1 = url;
  }

  _AddExercisePageState() {
    getImage('klatka.jpg');
  }
*/
  @override
  Widget build(BuildContext context) {
    print('test: ' + widget.trainingKey);
    return Scaffold(
        body: SafeArea(
      minimum: const EdgeInsets.all(56.0),
      child: Column(
        children: <Widget>[
          Row(
            children: [
              new GestureDetector(
                  onTap: () {
                    litems = chest;

                    setState(() {
                      _ref = FirebaseDatabase.instance
                          .reference()
                          .child('exercises')
                          .child('chest');
                    });
                    print('chest');
                  },
                  child: CircleAvatar(
                      radius: 35,
                      child: ClipRRect(
                        borderRadius: BorderRadius.circular(35),
                        child: Image.network(
                          'https://firebasestorage.googleapis.com/v0/b/fir-database-e91a5.appspot.com/o/klatka.jpg?alt=media&token=1a36212a-ed3b-4ce7-92c6-6714609060ee',
                          width: 62,
                          height: 62,
                          fit: BoxFit.fitHeight,
                          loadingBuilder: (BuildContext context, Widget child,
                              ImageChunkEvent loadingProgress) {
                            if (loadingProgress == null) return child;
                            return Center(
                              child: CircularProgressIndicator(
                                value: loadingProgress.expectedTotalBytes !=
                                        null
                                    ? loadingProgress.cumulativeBytesLoaded /
                                        loadingProgress.expectedTotalBytes
                                    : null,
                              ),
                            );
                          },
                        ),
                      ))),
              new GestureDetector(
                  onTap: () {
                    print("Container2 clicked");
                    litems = biceps;
                    setState(() {});
                  },
                  child: CircleAvatar(
                      radius: 35,
                      child: ClipRRect(
                        borderRadius: BorderRadius.circular(35),
                        child: Image.network(
                          'https://firebasestorage.googleapis.com/v0/b/fir-database-e91a5.appspot.com/o/biceps.jpg?alt=media&token=d88c9e6d-c56a-4aa0-9993-6bcae3c92c19',
                          width: 62,
                          height: 62,
                          fit: BoxFit.fitHeight,
                          loadingBuilder: (BuildContext context, Widget child,
                              ImageChunkEvent loadingProgress) {
                            if (loadingProgress == null) return child;
                            return Center(
                              child: CircularProgressIndicator(
                                value: loadingProgress.expectedTotalBytes !=
                                        null
                                    ? loadingProgress.cumulativeBytesLoaded /
                                        loadingProgress.expectedTotalBytes
                                    : null,
                              ),
                            );
                          },
                        ),
                      ))),
              new GestureDetector(
                  onTap: () {
                    print("Container3 clicked");
                  },
                  child: CircleAvatar(
                      radius: 35,
                      child: ClipRRect(
                        borderRadius: BorderRadius.circular(35),
                        child: Image.network(
                          'https://firebasestorage.googleapis.com/v0/b/fir-database-e91a5.appspot.com/o/triceps.jpg?alt=media&token=68b007f0-51f7-4a03-9164-9a1874436b60',
                          width: 62,
                          height: 62,
                          fit: BoxFit.fitHeight,
                          loadingBuilder: (BuildContext context, Widget child,
                              ImageChunkEvent loadingProgress) {
                            if (loadingProgress == null) return child;
                            return Center(
                              child: CircularProgressIndicator(
                                value: loadingProgress.expectedTotalBytes !=
                                        null
                                    ? loadingProgress.cumulativeBytesLoaded /
                                        loadingProgress.expectedTotalBytes
                                    : null,
                              ),
                            );
                          },
                        ),
                      ))),
              new GestureDetector(
                  onTap: () {
                    print("Container4 clicked");
                  },
                  child: CircleAvatar(
                      radius: 35,
                      child: ClipRRect(
                        borderRadius: BorderRadius.circular(35),
                        child: Image.network(
                          'https://firebasestorage.googleapis.com/v0/b/fir-database-e91a5.appspot.com/o/plecy.jpg?alt=media&token=b1b0ad96-6a1e-4b53-bcf2-200b8bb47f26',
                          width: 62,
                          height: 62,
                          fit: BoxFit.fitHeight,
                          loadingBuilder: (BuildContext context, Widget child,
                              ImageChunkEvent loadingProgress) {
                            if (loadingProgress == null) return child;
                            return Center(
                              child: CircularProgressIndicator(
                                value: loadingProgress.expectedTotalBytes !=
                                        null
                                    ? loadingProgress.cumulativeBytesLoaded /
                                        loadingProgress.expectedTotalBytes
                                    : null,
                              ),
                            );
                          },
                        ),
                      ))),
            ],
          ),
          ElevatedButton(
            child: const Text('Next Step'),
            onPressed: () async {
              //var url = await getImage('klatka.jpg');
              //print(url);
            },
          ),
          Text('Trening klatki piersiowej'),
          Text('Trening barków'),
          /*
          new Expanded(
              child: new ListView.builder(
                  itemCount: litems.length,
                  itemBuilder: (BuildContext ctxt, int Index) {
                    return new Text(litems[Index]);
                  })),*/
          Expanded(
              child: FirebaseAnimatedList(
                  query: _ref,
                  key: _key,
                  itemBuilder: (BuildContext context, DataSnapshot snapshot,
                      Animation<double> animation, int index) {
                    Map notes = snapshot.value;
                    return _buildContactItem(notes: notes, key: snapshot.key);
                  })),
        ],
      ),
    ));
  }
}