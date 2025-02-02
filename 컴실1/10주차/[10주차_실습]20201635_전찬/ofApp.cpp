#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    
    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5);
    if( draw_flag ){
        
        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */
        for(int i=0; i<line_counter; i++)
        {
            ofDrawLine(line_data[i][0], line_data[i][1], line_data[i][2], line_data[i][3]);
        }
        
        for(int i=0; i<dot_counter; i++)
        {
            if(selected_dot==i)
            {
                ofSetColor(255, 0, 0);
            }
            else{
                ofSetColor(0, 0, 0);
            }
            ofDrawCircle(dot_data[i][0], dot_data[i][1], 10);
        }
        
        // 2nd week portion.
        ofSetLineWidth(2);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){
        // Reset flags
        draw_flag = 0;
        
        // Free the dynamically allocated memory exits.
        for(int i=0; i<line_counter; i++)
        {
            delete(line_data[i]);
        }
        delete(line_data);
        
        for(int i=0; i<dot_counter; i++)
        {
            delete(dot_data[i]);
        }
        delete(dot_data);
        
        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return;
        
        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
        
        draw_flag = 1;
        selected_dot = 0;
    }
    if (key == 's'){
        // 2nd week portion.
    }
    if (key == 'e'){
        // 2nd week portion.
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 'l'){
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");
        
        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            
            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }
    
    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */
    
    if (key == OF_KEY_RIGHT){
        selected_dot = (selected_dot + 1)%dot_counter;
        
        cout << "Selcted Dot Coordinate is (" << dot_data[selected_dot][0] << ", " << dot_data[selected_dot][1] << ")" << endl;
    }
    
    if (key == OF_KEY_LEFT){
        if(selected_dot==0){
            selected_dot = dot_counter - 1;
        }
        else{
            selected_dot = selected_dot - 1;
        }
        
        cout << "Selcted Dot Coordinate is (" << dot_data[selected_dot][0] << ", " << dot_data[selected_dot][1] << ")" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    
    ofBuffer buffer(file);
    
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
    // 1. 동적할당 받기, 2. 범위를 벗어나는 놈은 제외시키기
    line_counter = 0;
    dot_counter = 0;
    int changeinputtype = 0;
    
    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
        if( words.size() == 1){
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
                
                line_data = new int*[num_of_line];
                for(int i=0; i<num_of_line; i++)
                {
                    line_data[i] = new int[4];
                }
            }
            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;
                
                dot_data = new int*[num_of_dot];
                for(int i=0; i<num_of_dot; i++)
                {
                    dot_data[i] = new int[4];
                }
            }
        }
        else if (words.size() >= 2){
            int x1,y1,x2,y2;
            if( input_type == 0){ // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());
                
                if(x1<0||x1>1024||y1<40||y1>728||x2<0||x2>1024||y2<40||y2>728)
                {
                    changeinputtype++;
                    continue;
                }
                else
                {
                    line_data[line_counter][0] = x1;
                    line_data[line_counter][1] = y1;
                    line_data[line_counter][2] = x2;
                    line_data[line_counter][3] = y2;
                    line_counter++;
                    changeinputtype++;
                }
                
                if(changeinputtype==num_of_line)
                {
                    input_type = 1;
                }
            }
            else{ // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                
                if(x1<0||x1>1024||y1<0||y1>728)
                {
                    continue;
                }
                
                dot_data[dot_counter][0] = x1;
                dot_data[dot_counter][1] = y1;
                dot_counter++;
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
    
    for(int i=line_counter; i<num_of_line; i++)
    {
        delete(line_data[i]);
    }
    line_data = (int**)realloc(line_data, line_counter*sizeof(int*));
    
    for(int j=dot_counter; j<num_of_dot; j++)
    {
        delete(dot_data[j]);
    }
    dot_data = (int**)realloc(dot_data, dot_counter*sizeof(int*));
    
    //initializeWaterLines();
}

void ofApp::initializeWaterLines() {
    ;
}


