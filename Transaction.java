package code_blockhain_project;

import java.util.ArrayList;
import java.util.List;

public class Transaction {

	private int transactionID;
	private int asNo;
	private int pathletID;
	private String ingress;
	private String egress;
	private double minBandwidth;
	private double maxDelay;
	private List<String> fullpath;
	private boolean status;

	public Transaction(int tID, int as, int pathId) {
		this.transactionID = tID;
		this.asNo = as;
		this.pathletID = pathId;
		this.minBandwidth = 0.0;
		this.maxDelay = 0.0;
		this.fullpath = new ArrayList<String>();
		this.status = true;
	}

	public int getTransactionID() {
		return this.transactionID;
	}

	public int getASNo() {
		return this.asNo;
	}

	public String getPathletId() {
		return String.valueOf(this.pathletID);
	}

	public void setIngressNode(String node) {
		this.ingress = node;
	}

	public String getIngressNode() {
		return this.ingress;
	}

	public void setEgressNode(String node) {
		this.egress = node;
	}

	public String getEgressNode() {
		return this.egress;
	}

	public String getStartNode() {
		return this.fullpath.get(0);
	}

	public String getEndNode() {
		return this.fullpath.get(fullpath.size() - 1);
	}

	public void setBandwidth(double bandwidth) {
		this.minBandwidth = bandwidth;
	}

	public double getMinBandwidth() {
		return this.minBandwidth;
	}

	public void setDelay(double delay) {
		this.maxDelay = delay;
	}

	public double getMaxDelay() {
		return this.maxDelay;
	}

	public void setFullPath(String path) {		
		
		String temp[] = path.split(",");

		if (!path.isEmpty() && !path.equalsIgnoreCase("[]")) {
			
			if (temp.length == 1) {
				temp[0] = temp[0].replaceAll("]", "");
			}
			
			for (int i = 0; i < temp.length; i++) {
				String value = "";

				if (i == 0) {
					value = temp[i].substring(1, temp[i].length());
					value = value.replaceAll("\\s", "");
					if (value.length()>3) {
						value = value.substring(value.length()/2);
					}
					
					value = String.format("%03d", this.asNo) + String.format("%03d", Integer.valueOf(value));
					setIngressNode(value);
				} else if (i == temp.length - 1) {
					value = temp[i].substring(0, temp[i].length() - 1);
					value = value.replaceAll("\\s", "");
					if (value.length()>3) {
						value = value.substring(value.length()/2);
					}
					
					value = String.format("%03d", this.asNo) + String.format("%03d", Integer.valueOf(value));
					setEgressNode(value);
				} else {
					value = temp[i];
					value = value.replaceAll("\\s", "");
					if (value.length() >= 3) {
						value = value.substring(value.length()/2);
					}
					value = String.format("%03d", this.asNo) + String.format("%03d", Integer.valueOf(value));
				}
				this.fullpath.add(value);
			}
		}
	}

	public List<String> getFullPath() {
		return this.fullpath;
	}

	public void setStatus(boolean stat) {
		this.status = stat;
	}

	public boolean getStatus() {
		return this.status;
	}

}
