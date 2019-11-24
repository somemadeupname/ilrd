package il.co.ilrd.vending_machine;

import java.time.LocalTime;
import java.util.Collection;

public class VendingMachine {

    private State state;
    private int currBalance;
    private Collection<Product> products;
    private ViewModule view;
    private Thread thread;
    private boolean active;
    private LocalTime startTime;

    public VendingMachine(Collection<Product> items, ViewModule view) {
        this.products = items;
        this.view = view;
        state = State.INIT;
        active = true;
        
        thread = new Thread ( () -> {

            while (active) {
                state.timeout(this);
                try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
            }
        });
    }

    /**
     * Initializes and invokes VendingMachine to begin state.
     */
    public void start() {
        thread.start();
        
        state.init(this);
    }

    /**
     * Shutdown the VendingMachine.
     */
    public void shutDown() {
        state.shutDown(this);
    }

    /**
     * Insert money into machine.
     * @param coinValue inserted for transaction.
     */
    public void insertCoin(int coinValue) {
        state.insertCoin(this, coinValue);
    }

    /**
     * Chooses product to buy.
     * @param chosen product.
     * invalid product will not have effect,
     * error message will be displayed in ViewModel.
     */
    public void chooseProduct(Product chosen) {
    	state.chooseProduct(this, chosen);
    }

    /**
     * cancels current transaction, and flushes change
     */
    public void cancel() {
        state.cancel(this);
    }

    private enum State {
        INIT {
            @Override
            void init(VendingMachine vm) {
            	vm.state.handleCurrentState(vm, IDLE);
            }
            
            @Override
            void handleCurrentState(VendingMachine vm, State state) {
            	vm.state = state;
            }
        },

        IDLE {
        	@Override
        	void insertCoin(VendingMachine vm, int coinValue) {
        		
        		COLLECTING_MONEY.insertCoin(vm, coinValue);
        	}

        	@Override
        	void handleCurrentState(VendingMachine vm, State state) {
        		vm.startTime = LocalTime.now();
        		vm.state = state;
        	}
        	
        },

        COLLECTING_MONEY {
            
        	@Override
            void insertCoin(VendingMachine vm, int coinValue) {
        		vm.currBalance += coinValue;
        		
        		vm.state.handleCurrentState(vm, COLLECTING_MONEY);
            }

            @Override
            void chooseProduct(VendingMachine vm, Product product) {
        		vm.startTime = LocalTime.now();
            	
        		if (!vm.products.contains(product)) {
            		vm.view.output("Product not available");
            		
            		vm.state.handleCurrentState(vm, COLLECTING_MONEY);
            		return;
            	}
            	
        		else if (vm.currBalance < product.price) {
            		vm.view.output("insufficiant funds. current balance is "
            												  + vm.currBalance);
            		vm.state.handleCurrentState(vm, COLLECTING_MONEY);
            		return;
            		
        		}
            	else {
            		vm.currBalance -= product.price;
            		vm.view.output("Dispensing product " + product.name);
            		vm.state.handleCurrentState(vm, TRANSACTION_COMPLETE);
            	}        		
            }

            void cancel(VendingMachine vm) {
            	
            	vm.state.returnChange(vm);
            	
            	vm.state.handleCurrentState(vm, IDLE);
            	
            }

            @Override
            void timeout(VendingMachine vm) {
            	if (vm.startTime.plusSeconds(CM_TO).isBefore(LocalTime.now())) {
            		vm.state.cancel(vm);
            	}
            }
            
            @Override
            void handleCurrentState(VendingMachine vm, State state) {
        		vm.startTime = LocalTime.now();
            	vm.state = state;
            }
            
        },

        TRANSACTION_COMPLETE {
            @Override
            void timeout(VendingMachine vm) {
            	            	
            	if (vm.startTime.plusSeconds(TC_TO).isBefore(LocalTime.now())) {
            	
            		vm.view.output("Transaction complete");
            		
            		vm.state.returnChange(vm);
            		
            		vm.state.handleCurrentState(vm, IDLE);
            	}
            }
            
            @Override
            void handleCurrentState(VendingMachine vm, State state) {
        		vm.startTime = LocalTime.now();
            	vm.state = state;
            }
        };

        /*
         *  Will initialize Vending machine, change to waitForProduct state
         * @param vm - current Vending Machine
         */
        void init(VendingMachine vm) {

        }
        
        /*
         *  Will shut down Vending machine, change change active flag to false
         * @param vm - current Vending Machine
         */
        void shutDown(VendingMachine vm) {
        	vm.active = false;
        	
        	try {
				vm.thread.join();
			} catch (InterruptedException e) {
				System.err.println("error joining thread");
			}
        }
        /*
         * Handles payment transaction, increases current balance,
         * changes state to WAIT_FOR_PRODUCT if there is sufficient balance.
         */
        void insertCoin(VendingMachine vm, int money) {

        }

        /*
         * Changes selected product in vm, changes state to waitForMoney
         */
        void chooseProduct(VendingMachine vm, Product product) {
        }

        /*
         * @param vm cancels current transaction,
         *  changes state to waitForProduct
         */
        void cancel(VendingMachine vm) {
        }

        /*
         * @param vm 
         *  handles timeout event 
         */
        void timeout(VendingMachine vm) {
        }
        
        /*
         * @param vm 
         * sets start time to current time of state transition
         */
        abstract void handleCurrentState(VendingMachine vm, State state);
        
        void returnChange(VendingMachine vm) {
        	vm.view.output("flushing " + vm.currBalance + " in change.");
        	vm.currBalance = 0;
        }
        
        /* Timeouts for Trancaction Complete and Collecting Money states */
        private final static int TC_TO = 5; 
        private final static int CM_TO = 10;
    }

    public static class Product {
        private String name;
        private int price;

        Product(String name, int price) {
            this.price = price;
            this.name = name;
        }

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + ((name == null) ? 0 : name.hashCode());
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Product other = (Product) obj;
			if (name == null) {
				if (other.name != null)
					return false;
			} else if (!name.equals(other.name))
				return false;
			return true;
		}

    }

}