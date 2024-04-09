# Collecting MLOps Data In Aupera’s License Plate Recognition (LPR) Application

1. Create an LPR Task with MLOps feature enabled. 
To do this, click on "Change task Parameters" and enable "MLOps Mode" checkbox. 
    - You can also enable MLOps mode if you already have an active LPR Task. 
    Click on "Controls", and then "Reconfigure LPR Task" and enable MLOps mode from there.

2. Allow some time for MLOps data to be collected.
You can view the collected images under "MLOps Data" tab. 
Each tracklet represents a single detected car. 

3. Under the "MLOps Data" tab you can filter MLOps results by date. 
You can choose a date range or select **Hour**, **Day**, **Week** buttons for quick filters. 
Click on the **Download MLOps Results** button beside the date picker to start downloading MLOps images in your selected time range.
    - If no date range is selected, all collected data will be downloaded
    - If it's the first time using this feature, you may need to enable popups for this website to be able to download the archive
      <div align="center">
        <img 
            width="40%"
            src="./imgs/2.2.10.png" 
            alt="Alt text"
        >
      </div>

    - You can download archives up to 10GB. If you get an error indicating that the archive is larger, consider specifying a narrower time range.
    - Download will start automatically when the archive is ready, it may take some time to prepare the archive. **Do not close the tab while preparing the archive**.

