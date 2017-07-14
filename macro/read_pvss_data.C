{
	//
	// Get PVSS Data
	//
	std::ifstream ifs("/Users/alberto/Software/WA105/WA105_LightSoft/PVSS_data/grid_HV_0711_0712.txt", std::ifstream::in);

	int nlines = 0;
    int ts_raw;
	double vv_raw;

	if (!ifs.is_open()) {
		cout << "file not open!" << endl;
		return;
	}
	
	while (ifs.good()) {
       ifs >> ts_raw >> vv_raw;
	   std::cout << ts_raw << " " << vv_raw << std::endl;
	   nlines++;
    }
	
	cout << nlines << endl;

}